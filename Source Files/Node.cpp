//
// Created by damak on 08.04.2025.
//
#include <vector>

#include "../Header Files/Node.h"

using namespace std;

/**
 * Конструктор класса Node
 * @param number - числовое значение узла
 * @param arity - арность узла
 */
Node::Node(const int &number, const int &arity) : number(number), arity(arity) {
    // Инициализируем вектор размером arity потомков, где по умолчанию каждый потомок - nullptr
    children.resize(arity, nullptr);
}

/**
 * Получить числовое значение узла
 * @return Числовое значение узла
 */
int Node::getNumber() const {
    return this->number;
}

/**
 * Получить арность узла
 * @return Арность узла
 */
int Node::getArity() const {
    return this->arity;
}

/**
 * Получить всех потомков узла
 * @return Вектор потомков узла
 */
vector<Node*>& Node::getChildren() {
    return this->children;
}

/**
 * Получить потомка по индексу
 * @param number - индекс потомка
 * @return Потомок узла
 */
Node* Node::getChild(const int& number) const {
    return this->children[number];
}