//
// Created by damak on 10.04.2025.
//

#include <vector>

#include "../Header Files/FinderLongestOddPath.h"

/**
 * Находит самый длинный путь от корня, проходящий только по вершинам с нечётными номерами
 * @param node - текущий узел
 * @param currentPath - текущий путь
 * @param longestPath - самый длинный найденный путь
 */
void FinderLongestOddPath::findLongestOddPath(Node* node, vector<int>& currentPath, vector<int>& longestPath) {
    if (!node) return;

    // Если узел чётный - прекращаем поиск по этой ветке
    if (node->getNumber() % 2 == 0) return;

    // Добавляем текущий путь в узел
    currentPath.push_back(node->getNumber());

    // Проверка, не стал ли текущий путь длиннее найденного ранее
    if (currentPath.size() > longestPath.size()) {
        longestPath = currentPath;
    }

    // Рекурсивный обход по всем потомкам
    for (int i = 0; i < node->getArity(); i++) {
        if (Node* child = node->getChild(i)) findLongestOddPath(child, currentPath, longestPath);
    }

    // Удаляем текущий узел из пути при возврате из рекурсии
    currentPath.pop_back();
}
