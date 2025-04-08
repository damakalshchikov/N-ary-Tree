//
// Created by damak on 08.04.2025.
//

#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

class Node {
public:
    Node(const int& number, const int& arity);

    int getNumber() const;

    int getArity() const;

    vector<Node*>& getChildren();

    Node* getChild(const int& number) const;

private:
    int number;
    int arity;
    vector<Node*> children;
};

#endif //NODE_H
