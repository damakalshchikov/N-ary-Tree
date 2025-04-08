//
// Created by damak on 08.04.2025.
//

#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

/**
 * Класс, представляющий узел n-арного дерева
 */
class Node {
public:
    /**
     * Конструктор класса Node
     * @param number - числовое значение узла
     * @param arity - арность узла
     */
    Node(const int& number, const int& arity);

    /**
     * Получить числовое значение узла
     * @return Числовое значение узла
     */
    int getNumber() const;

    /**
     * Получить арность узла
     * @return Арность узла
     */
    int getArity() const;

    /**
     * Получить всех потомков узла
     * @return Вектор потомков узла
     */
    vector<Node*>& getChildren();

    /**
     * Получить потомка по индексу
     * @param number - индекс потомка
     * @return Потомок узла
     */
    Node* getChild(const int& number) const;

private:
    // Числовое значение, арность и потомки узла
    int number;
    int arity;
    vector<Node*> children;
};

#endif //NODE_H
