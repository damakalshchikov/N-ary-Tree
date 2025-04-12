//
// Created by damak on 10.04.2025.
//

#ifndef FINDERLONGESTODDPATH_H
#define FINDERLONGESTODDPATH_H

#include <vector>

#include "Node.h"

class FinderLongestOddPath {
public:
    /**
     * Находит самый длинный путь от корня, проходящий только по вершинам с нечётными номерами
     * @param node - текущий узел
     * @param currentPath - текущий путь
     * @param longestPaths - самый длинный найденный путь
     * @param maxLength - максимальная длина найденного пути
     */
    static void findLongestOddPath(Node* node, vector<int>& currentPath, vector<vector<int>>& longestPaths, int maxLength);
};

#endif //FINDERLONGESTODDPATH_H
