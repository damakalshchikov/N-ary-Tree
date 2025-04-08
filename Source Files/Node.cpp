//
// Created by damak on 08.04.2025.
//
#include <vector>

#include "../Header Files/Node.h"

using namespace std;

Node::Node(const int &number, const int &arity) : number(number), arity(arity) {
    // Инициализируем вектор размером arity потомков, где по умолчанию каждый потомок - nullptr
    children.resize(arity, nullptr);
}

int Node::getNumber() const {
    return this->number;
}

int Node::getArity() const {
    return this->arity;
}

vector<Node*>& Node::getChildren() {
    return this->children;
}

Node* Node::getChild(const int& number) const {
    return this->children[number];
}