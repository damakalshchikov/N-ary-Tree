//
// Created by damak on 08.04.2025.
//

#include <string>
#include <fstream>
#include <iostream>

#include "../Header Files/FileReader.h"

using namespace std;

/**
 * Читает файл и преобразует строки в узлы дерева или nullptr
 * @param fileName - имя файла
 * @return Вектор указателей на узлы дерева
 */
vector<Node*> FileReader::readFile(const string& fileName) {
    vector<Node*> tree;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) throw runtime_error("Не удалось открыть файл: " + fileName);

    getline(file, line);
    // Арность дерева
    const int arity = stoi(line);

    while (getline(file, line)) {
        // Удаляем служебные символы
        line.erase(0, line.find_first_not_of("\t\r\n"));
        line.erase(line.find_last_not_of("\t\r\n") + 1);

        if (line == "None") {
            tree.push_back(nullptr);
        }
        else {
            int number = stoi(line);
            tree.push_back(new Node(number, arity));
        }
    }

    file.close();
    return tree;
}

/**
 * Устанавливает связи между вершинами в соответствии со структурой файла
 * @param tree - вектор указателей на узлы дерева
 * @param arity - арность дерева
 */
void FileReader::buildTreeConnections(vector<Node*>& tree, const int& arity) {
    int limit = tree.size();
    int noneCount = 0;

    for (int i = 0; i < limit; i++) {
        Node* node = tree[i];

        if (!node) {
            noneCount += arity;
            continue;
        }

        // Индекс для вычисления потомков
        int childIndex = i * arity - noneCount;

        for (int j = 1; j <= arity; j++) {

            if (childIndex < limit) {
                node->getChildren()[j - 1] = tree[childIndex + j];
            }
        }
    }
}

/**
 * Освобождает память, выделенную под дерево
 * @param tree - вектор указателей на узлы дерева
 */
void FileReader::cleanUpTree(vector<Node*>& tree) {
    for (auto node: tree) {
        if (node) delete node;
    }

    tree.clear();
}