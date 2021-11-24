#pragma once
#include <QGraphicsLineItem>
#include <QColor>

class Node;

class Link : public QGraphicsLineItem {
public:
    Link(Node *fromNode, Node *toNode);
    ~Link();

    Node *fromNode() const;
    Node *toNode() const;

    void setColor(const QColor &color);
    QColor color() const;

    void trackNodes();

private:
    Node *myFromNode;
    Node *myToNode;
};