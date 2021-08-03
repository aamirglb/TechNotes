#include <QQuickItem>
#include <QSGNode.

class QQuickCustomItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    QQuickCustomItem(QQuickItem *parent = Q_NULLPTR);
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData);
    QColor color() const;
    void setColor(const QColor &color);
private:
    QColor m_color;
    bool m_needUpdate;
signals:
    void colorChanged();
};
