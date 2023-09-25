//widget.cpp
#include "widget.h"
#include <QDebug>

widget::widget(QWidget *parent)
    : QMainWindow(parent)
{   
    application = static_cast<QApplication*>(QApplication::instance());
    mainLayout = new QVBoxLayout();
    loop = false;

    startButton = new QPushButton("START");
    mainLayout->addWidget(startButton);

    connect(startButton, SIGNAL(clicked()),this,SLOT(onStartButtonPressed()));

    centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->showMaximized();
    this->setWindowTitle("Widget");    
}
    
void widget::onStartButtonPressed()
{
    loop = !loop;
    startButton->setText(loop? "STOP" : "START");
    start();    
}

void widget::start()
{
    while(loop)
    {
        application->processEvents();
    }
    qDebug() << "Loop ends";
}


widget::~widget()
{
    loop = false;
}