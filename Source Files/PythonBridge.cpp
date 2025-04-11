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
        // Инициализация Python интерпретатора
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
    // Остановка Python интерпретатора
    if (isPythonInitialized) {
        Py_Finalize();
        isPythonInitialized = false;
    }
}

/**
 * Создаёт изображение n-арного дерева
 * @param tree - вектор указателей на узлы n-арного дерева
 * @param path
 * @param outputPng - имя выходного изображения
 */
void PythonBridge::drawTree(const vector<Node *> &tree, const vector<int> &path, const string &outputPng) {
    // Если Python интерпретатор не инициализирован, то инициализируем его
    if (!isPythonInitialized) {
        initialize();
    }

    // Импортирование модуля, который содержит функцию визуализации n-арного дерева
    PyObject* pModule = PyImport_ImportModule("Python.visualizer");
    PyObject* drawTreeFunc = PyObject_GetAttrString(pModule, "draw_tree");
    // Список, который содержит представление узлов n-арного дерева понятное интерпретатору Python
    PyObject* nodeList = PyList_New(tree.size());

    // noneCount - счётчик "пустых" узлов
    // arity - арность дерева
    int noneCount = 0;
    int arity = tree[0]->getArity();

    for (int i = 0; i < tree.size(); i++) {
        if (tree[i]) {
            // Атрибуты узла
            PyObject* nodeDict = PyDict_New();

            // Номер узла и его арность
            PyDict_SetItemString(nodeDict, "number", PyLong_FromLong(tree[i]->getNumber()));
            PyDict_SetItemString(nodeDict, "arity", PyLong_FromLong(tree[i]->getArity()));

            // Индекс потомка
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

            // Добавляем узел в общий список узлов
            PyList_SetItem(nodeList, i, nodeDict);
        }
        else {
            Py_INCREF(Py_None);
            // Если узел "пусто" - вместо него добавляем None, и увеличиваем счётчик на арность
            PyList_SetItem(nodeList, i, Py_None);
            noneCount += arity;
        }
    }

    // Список, который содержит найденный длинный путь с нечётными номерами
    PyObject* pathList = nullptr;

    if (!path.empty()) {
        pathList = PyList_New(path.size());
        for (int i = 0; i < path.size(); i++)
            PyList_SetItem(pathList, i, PyLong_FromLong(path[i]));
    }
    else {
        Py_INCREF(Py_None);
        pathList = Py_None;
    }

    // Подготавливаем аргументы для вызова Python-функции
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, nodeList);
    PyTuple_SetItem(args, 1, pathList);
    PyTuple_SetItem(args, 2, PyUnicode_FromString(outputPng.c_str()));

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