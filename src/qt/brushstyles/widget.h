#include <QWidget>

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
};