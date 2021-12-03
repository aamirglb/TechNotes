#pragma once

#include <QWidget>

class Ticker : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    Ticker(QWidget *parent = nullptr);
    QString text() const { return myText; }
    QSize sizeHint() const;

public slots:
    void setText(const QString &newText);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    QString myText;
    int offset;
    int myTimerId;
};