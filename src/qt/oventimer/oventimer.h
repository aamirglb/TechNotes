#include <QWidget>
#include <QDateTime>

class OvenTimer : public QWidget
{
    Q_OBJECT
public:
    OvenTimer(QWidget *parent = 0);
    void setDuration(int secs);
    int duration() const;
    void draw(QPainter *painter);

signals:
    void timeout();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //QSize sizeHint() const override;
    void resizeEvent(QResizeEvent * event) override;

private:
    QDateTime finishTime;
    QTimer *updateTimer;
    QTimer *finishTimer;
};