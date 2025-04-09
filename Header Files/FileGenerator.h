//
// Created by damak on 10.04.2025.
//

#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <string>

using namespace std;

class FileGenerator {
public:
    /**
     * Генерирует файл с описанием n-арного дерева
     * @param fileName - имя файла
     * @param arity - арность дерева
     * @param nodeCount - количество узлов
     */
    static void generateTreeFile(const string& fileName, int& arity, int& nodeCount);
};

#endif //FILEGENERATOR_H
