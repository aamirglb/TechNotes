#include "link.h"
#include "node.h"
#include <QPen>

Link::Link(Node *fromNode, Node *toNode) {
    myFromNode = fromNode;
    myToNode = toNode;

    myFromNode->addLink(this);
    myToNode->addLink(this);

    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);

    setColor(Qt::darkRed);
    trackNodes();
}

Link::~Link() {
    myFromNode->removeLink(this);
    myToNode->removeLink(this);
}

void Link::setColor(const QColor &color) {
    setPen(QPen(color, 1.0));
}

QColor Link::color() const {
    return pen().color();
}
void Link::trackNodes() {
    setLine(QLineF(myFromNode->pos(), myToNode->pos()));
}

