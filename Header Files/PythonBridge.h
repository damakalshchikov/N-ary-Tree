//
// Created by damak on 10.04.2025.
//

#ifndef PYTHONBRIDGE_H
#define PYTHONBRIDGE_H

#include <string>
#include <vector>
#include "Node.h"

using namespace std;

/**
 * Класс для взаимодействия с Python
 */
class PythonBridge {
public:
    /**
     * Инициализирует интерпретатор Python
     */
    static void initialize();

    /**
     * Освобождает ресурсы Python
     */
    static void finalize();

    /**
     * Создаёт изображение n-арного дерева
     * @param tree - вектор указателей на узлы n-арного дерева
     * @param path - найденный путь с нечётными вершинами
     * @param outputPng - имя выходного изображения
     */
    static void drawTree(const vector<Node*>& tree, const vector<int>& path, const string& outputPng = "./Images/tree.png");

private:
    static bool isPythonInitialized;
};

#endif //PYTHONBRIDGE_H
