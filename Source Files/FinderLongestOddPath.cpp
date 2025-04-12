//
// Created by damak on 10.04.2025.
//

#include <vector>

#include "../Header Files/FinderLongestOddPath.h"

/**
 * Находит самый длинный путь от корня, проходящий только по вершинам с нечётными номерами
 * @param node - текущий узел
 * @param currentPath - текущий путь
 * @param longestPaths - самый длинный найденный путь
 * @param maxLength - максимальная длина найденного пути
 */
void FinderLongestOddPath::findLongestOddPath(Node* node, vector<int>& currentPath, vector<vector<int>>& longestPaths, int maxLength) {
    if (!node) return;

    // Если узел чётный - прекращаем поиск по этой ветке
    if (node->getNumber() % 2 == 0) return;

    currentPath.push_back(node->getNumber());

    if (currentPath.size() > maxLength) {
        longestPaths.clear();
        longestPaths.push_back(currentPath);
        maxLength = currentPath.size();
    }
    else if (currentPath.size() == maxLength) {
        longestPaths.push_back(currentPath);
    }

    for (int i = 0; i < node->getArity(); i++) {
        if (Node* child = node->getChild(i)) {
            findLongestOddPath(child, currentPath, longestPaths, maxLength);
        }
    }

    currentPath.pop_back();
}
