#include <QWidget>

class QTimer;

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int32_t w{400};
    int32_t h{400};
    int32_t angle{0};
    QTimer *timer;
};