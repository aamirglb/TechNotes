#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>
#include <QPushButton>
#include <QLayout>

#include "findfiledialog.h"

FindFileDialog::FindFileDialog(QWidget *parent)
    : QWidget(parent) {

    namedLabel = new QLabel("Named: ", this);
    namedLineEdit = new QLineEdit(this);
    lookInLabel = new QLabel("Look in: ", this);
    lookInLineEdit = new QLineEdit(this);
    subfoldersCheckBox = new QCheckBox("Include subfolders", this);
    tableWidget = new QTableWidget(this);
    messageLabel = new QLabel("0 files found", this);
    findButton = new QPushButton("Find", this);
    stopButton = new QPushButton("Stop", this);
    closeButton = new QPushButton("Close", this);
    helpButton = new QPushButton("Help", this);

    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("In Folder"));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(namedLabel, 0, 0);
    leftLayout->addWidget(namedLineEdit, 0, 1);
    leftLayout->addWidget(lookInLabel, 1, 0);
    leftLayout->addWidget(lookInLineEdit, 1, 1);
    leftLayout->addWidget(subfoldersCheckBox, 2, 0, 1, 2);
    leftLayout->addWidget(tableWidget, 3, 0, 1, 2);
    leftLayout->addWidget(messageLabel, 4, 0, 1, 2);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(stopButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();
    rightLayout->addWidget(helpButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find Files or Folders"));
}

