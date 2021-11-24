#include <QPainter>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(800, 800);
}

void Widget::paintEvent(QPaintEvent * /* evnet */) {
    QPainter painter(this);

    Qt::BrushStyle styles[] = {
        Qt::SolidPattern,
        Qt::Dense1Pattern,
        Qt::Dense2Pattern,
        Qt::Dense3Pattern,
        Qt::Dense4Pattern,
        Qt::Dense5Pattern,
        Qt::Dense6Pattern,
        Qt::Dense7Pattern,
        Qt::NoBrush,
        Qt::HorPattern,
        Qt::VerPattern,
        Qt::CrossPattern,
        Qt::BDiagPattern,
        Qt::FDiagPattern,
        Qt::DiagCrossPattern,
        Qt::LinearGradientPattern,
        Qt::RadialGradientPattern,
        Qt::ConicalGradientPattern
    };

    auto x = 10;
    auto y = 10;
    for(auto i = 0; i < 18; ++i) {
        painter.setBrush(QBrush(Qt::green, styles[i]));
        painter.drawRect(x, y, 50, 50);

        x += 60;
        if((x+60) > 800) {
            x = 10;
            y += 70;
        }
    } 

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(40, 150, 200, 120);

    painter.setPen(QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter.setBrush(QBrush(Qt::blue, Qt::DiagCrossPattern));
    painter.drawPie(260, 150, 200, 120, 60*16, 270*16);

    QPainterPath path;
    path.moveTo(80, 320);
    path.cubicTo(200, 80, 320, 80, 480, 320);
    painter.setPen(QPen(Qt::black, 8));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);

}
