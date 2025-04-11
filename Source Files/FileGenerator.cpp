//
// Created by damak on 10.04.2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

#include "../Header Files//FileGenerator.h"

/**
 * Генерирует файл с описанием n-арного дерева
 * @param fileName - имя файла
 * @param arity - арность дерева
 * @param nodeCount - количество узлов
 */
void FileGenerator::generateTreeFile(const string &fileName, int &arity, int &nodeCount) {
    ofstream file(fileName);

    if (!file.is_open()) wcout << L"Не удалось открыть файл для записи" << endl;

    // Записываем арность дерева
    file << arity << endl;

    // Генератор случайных чисел
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> valuse(1, 100);

    // Вектор структуры дерева
    vector<bool> tree(nodeCount, false);

    // Задаём корень
    tree[0] = true;

    for (int i = 0; i < nodeCount; i++) {
        if (!tree[i]) continue;

        for (int j = 0; j < arity; j++) {
            // Индекс потомка
            int childIndex = i * arity + j + 1;

            if (childIndex < nodeCount) {
                // 90% вероятность создания узла
                tree[childIndex] = (rng() % 100 < 101);
            }
        }
    }

    for (int i = 0; i < nodeCount; i++) {
        if (tree[i]) {
            int value = valuse(rng);
            file << value << endl;
        }
        else {
            file << "None" << endl;
        }
    }

    file.close();
}
