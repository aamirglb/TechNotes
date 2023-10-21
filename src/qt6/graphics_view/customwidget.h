#pragma once
#include <QtWidgets>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);
private:
    QGraphicsView *m_View;
    QGraphicsScene *m_Scene;
};
