#include "node.h"

Node::Node(Type type, const QString &str) {
    this->type = type;
    this->str = str;
    parent = nullptr;
}

Node::~Node() {
    qDeleteAll(children);
}



