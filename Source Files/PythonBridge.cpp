//
// Created by damak on 10.04.2025.
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <vector>

#include "../Header Files/PythonBridge.h"

using namespace std;

bool PythonBridge::isPythonInitialized = false;

/**
 * Инициализирует интерпретатор Python
 */
void PythonBridge::initialize() {
    if (!isPythonInitialized) {
        Py_Initialize();

        PyRun_SimpleString("import sys\n"
                           "import os\n"
                           "sys.path.append(os.getcwd())\n");

        isPythonInitialized = true;
    }
}

/**
 * Освобождает ресурсы Python
 */
void PythonBridge::finalize() {
    if (isPythonInitialized) {
        Py_Finalize();
        isPythonInitialized = false;
    }
}

/**
 * Создаёт изображение n-арного дерева
 * @param tree - вектор указателей на узлы n-арного дерева
 * @param outputPng - имя выходного изображения
 */
void PythonBridge::drawTree(const vector<Node*>& tree, const string& outputPng) {
    if (!isPythonInitialized) {
        initialize();
    }

    PyObject* pModule = PyImport_ImportModule("Python.visualizer");
    PyObject* drawTreeFunc = PyObject_GetAttrString(pModule, "draw_tree");
    PyObject* nodeList = PyList_New(tree.size());

    int noneCount = 0;
    int arity = tree[0]->getArity();

    for (int i = 0; i < tree.size(); i++) {
        if (tree[i]) {
            PyObject* nodeDict = PyDict_New();

            PyDict_SetItemString(nodeDict, "number", PyLong_FromLong(tree[i]->getNumber()));
            PyDict_SetItemString(nodeDict, "arity", PyLong_FromLong(tree[i]->getArity()));

            const int childIndex = i * arity - noneCount;

            for (int j = 0; j < arity; j++) {
                const auto& child = tree[i]->getChild(j);
                string dictKey = "child" + to_string(j);

                if (child) PyDict_SetItemString(nodeDict, dictKey.c_str(), PyLong_FromLong(childIndex + j + 1));
                else {
                    PyDict_SetItemString(nodeDict, dictKey.c_str(), Py_None);
                    Py_INCREF(Py_None);
                }
            }

            PyList_SetItem(nodeList, i, nodeDict);
        }
        else {
            Py_INCREF(Py_None);
            PyList_SetItem(nodeList, i, Py_None);
            noneCount += arity;
        }
    }

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, nodeList);
    PyTuple_SetItem(args, 1, PyUnicode_FromString(outputPng.c_str()));

    PyObject* result = PyObject_CallObject(drawTreeFunc, args);
    if (!result) {
        PyErr_Print();
    }

    // Освобождаем ресурсы
    Py_XDECREF(result);
    Py_DECREF(args);
    Py_DECREF(drawTreeFunc);
    Py_DECREF(pModule);
}