//
// Created by damak on 08.04.2025.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>

#include "Node.h"

using namespace std;

/**
 * Класс для чтения файлов и создания структуры дерева
 */
class FileReader {
public:
    /**
     * Читает файл и преобразует строки в узлы дерева или nullptr
     * @param fileName - имя файла
     * @param arity - арность дерева
     * @return Вектор указателей на узлы дерева
     */
    static vector<Node*> readFile(const string& fileName, const int& arity);

    /**
     * Устанавливает связи между вершинами в соответствии со структурой файла
     * @param tree - вектор указателей на узлы дерева
     * @param arity - арность дерева
     */
    static void buildTreeConnections(vector<Node*>& tree, const int& arity);
};

#endif //FILEREADER_H
