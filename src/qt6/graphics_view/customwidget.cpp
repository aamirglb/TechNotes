#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{
    m_View = new QGraphicsView(this);
    m_Scene = new QGraphicsScene(this);
    m_View->setScene(m_Scene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_View);
    setLayout(layout);

    QGraphicsItem* rect1 = m_Scene->addRect(0, 0, 40, 40, Qt::NoPen, QColor("#FFBB33"));
    rect1->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable);
}