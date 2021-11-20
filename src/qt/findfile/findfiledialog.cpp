#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>
#include <QPushButton>

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
    setMinimumSize(265, 190);
    resize(365, 240);
}

void FindFileDialog::resizeEvent(QResizeEvent * /* event */) {
    int extraWidth = width() - minimumWidth();
    int extraHeight = height() - minimumHeight();
    namedLabel->setGeometry(9, 9, 50, 25);
    namedLineEdit->setGeometry(65, 9, 100 + extraWidth, 25);
    lookInLabel->setGeometry(9, 40, 50, 25);
    lookInLineEdit->setGeometry(65, 40, 100 + extraWidth, 25);
    subfoldersCheckBox->setGeometry(9, 71, 156 + extraWidth, 23);
    tableWidget->setGeometry(9, 100, 156 + extraWidth,     50 + extraHeight);
    messageLabel->setGeometry(9, 156 + extraHeight, 156 + extraWidth,     25);
    findButton->setGeometry(171 + extraWidth, 9, 85, 32);
    stopButton->setGeometry(171 + extraWidth, 47, 85, 32);
    closeButton->setGeometry(171 + extraWidth, 84, 85, 32);
    helpButton->setGeometry(171 + extraWidth, 149 + extraHeight, 85, 32);
}

