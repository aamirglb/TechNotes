#include <QApplication>
#include "plotter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Plotter *plot = new Plotter;

    QVector< QVector<QPointF> > points(4);
    
    for(auto i = .5; i < 10.5; i+=.5) {
        points[0].push_back(QPointF(i, i*i));
        points[1].push_back(QPointF(i, (i*i) + 2.5));
        points[2].push_back(QPointF(i, i*2.));
        points[3].push_back(QPointF(i, i));
    }
    plot->setCurveData(0, points[0]);
    plot->setCurveData(1, points[1]);
    plot->setCurveData(2, points[2]);
    plot->setCurveData(3, points[3]);
    plot->show();
    return app.exec();
}