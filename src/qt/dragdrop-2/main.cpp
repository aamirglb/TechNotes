#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include <QPushButton>
#include <QListWidgetItem>

#include "projectlistwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *projA = new ProjectListWidget;
    auto *projB = new ProjectListWidget;

    QStringList teamA;
    teamA << "Mohammad" << "Aamir" << "Ali";
    for(const auto &s : teamA)
        new QListWidgetItem(s, projA);

    QStringList teamB;
    teamB << "Mohammed" << "Umar" << "Ali";
    for(const auto &s : teamB)
        new QListWidgetItem(s, projB);


    auto *leftButton = new QPushButton;
    leftButton->setIcon(QIcon(":/images/left-arrow.png"));
    auto *rightButton = new QPushButton;
    rightButton->setIcon(QIcon(":/images/right-arrow.png"));

    QObject::connect(leftButton,  &QPushButton::clicked, [&](){ projB->moveItem(projA); });
    QObject::connect(rightButton, &QPushButton::clicked, [&](){ projA->moveItem(projB); });

    auto *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(new QLabel("<b>Project A</b>"));
    leftLayout->addWidget(projA);

    auto *middleLayout = new QVBoxLayout;
    middleLayout->setAlignment(Qt::AlignCenter);
    middleLayout->addWidget(leftButton);
    middleLayout->addWidget(rightButton);

    auto *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(new QLabel("<b>Project B</b>"));
    rightLayout->addWidget(projB);

    auto *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(rightLayout);

    auto *window = new QWidget;
    window->setLayout(mainLayout);
    window->show();
    return app.exec();
}
