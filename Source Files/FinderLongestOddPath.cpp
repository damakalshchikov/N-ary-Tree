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
 */
void FinderLongestOddPath::findLongestOddPath(Node* node, vector<int>& currentPath, vector<vector<int>>& longestPaths) {
    if (!node) return;

    // Если узел чётный - прекращаем поиск по этой ветке
    if (node->getNumber() % 2 == 0) return;

    // Добавляем текущий узел в путь
    currentPath.push_back(node->getNumber());

    bool isLeafPath = true;
    for (int i = 0; i < node->getArity(); i++) {
        Node* child = node->getChild(i);
        if (child && child->getNumber() % 2 != 0) {
            isLeafPath = false;
            break;
        }
    }

    if (isLeafPath) {
        if (longestPaths.empty() || currentPath.size() > longestPaths[0].size()) {
            // Если текущий путь длиннее всех найденных, очищаем список и добавляем новый
            longestPaths.clear();
            longestPaths.push_back(currentPath);
        } else if (!longestPaths.empty() && currentPath.size() == longestPaths[0].size()) {
            // Если текущий путь такой же длины как максимальный, добавляем этот путь
            longestPaths.push_back(currentPath);
        }
    }

    // Рекурсивный обход по всем потомкам
    for (int i = 0; i < node->getArity(); i++) {
        if (Node* child = node->getChild(i)) {
            findLongestOddPath(child, currentPath, longestPaths);
        }
    }

    currentPath.pop_back();
}
