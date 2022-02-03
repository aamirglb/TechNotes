#include <QPainter>
#include <QTimer>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(w, h);
    timer = new QTimer;
    timer->setInterval(50);
    connect(timer, &QTimer::timeout, [&](){ angle += 1; update();});
    timer->start();
}

void Widget::paintEvent(QPaintEvent * /* evnet */) {
    QPainter painter(this);
    painter.translate(w/2, h/2);
    painter.rotate(angle);
    painter.translate(-w/2, -h/2);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawRect(w/2-50, h/2-50, 100, 100);

    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(w/2-10, h/2-10, 20, 20);
}
