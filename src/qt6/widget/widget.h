//widget.h
#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QLayout>

class widget : public QMainWindow
{
    Q_OBJECT

public:
    QApplication* application;
    widget(QWidget *parent = nullptr);
    QVBoxLayout *mainLayout;
    QPushButton *startButton;
    QWidget *centralWidget;

    ~widget();

public slots:
    void onStartButtonPressed();


private:

    void start();
    bool loop;

};
