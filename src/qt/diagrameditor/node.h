#pragma once
#include <QGraphicsItem>
#include <QColor>
#include <QSet>

class QPainter;
class QStyleOptionGraphicsItem;
class QGraphicsScenceMouseEvent;

class Node : public QGraphicsItem {
    Q_DECLARE_TR_FUNCTIONS(Node);

public:
    Node();
    void setText(const QString &text) { myText = text; }
    QString text() const { return myText; }

    void setTextColor(const QColor &color) { myTextColor = color; }
    QColor textColor() const { return myTextColor; }

    void setOutlineColor(const QColor &color) { myOutlineColor = color; }
    QColor outlineColor() const { return myOutlineColor; }

    void setBackgroundColor(const QColor &color) { myBackgroundColor = color; }
    QColor backgroundColor() const { return myBackgroundColor; }

    void addLink(Link *link);
    void removeLink(Link *link);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void mouseDoubleClickEvent(QGraphicsScenceMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    QSet<Link *> myLinks;
    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
};