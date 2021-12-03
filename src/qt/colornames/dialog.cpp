#include "dialog.h"

#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QListView>
#include <QComboBox>
#include <QLineEdit>
#include <QColor>
#include <QRegExp>
#include <QLayout>
#include <QLabel>

ColorNamesDialog::ColorNamesDialog(QWidget *parent) 
    : QDialog(parent) {
    sourceModel = new QStringListModel(this);
    sourceModel->setStringList(QColor::colorNames());

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sourceModel);
    proxyModel->setFilterKeyColumn(0);

    listView = new QListView;
    listView->setModel(proxyModel);

    filterLineEdit = new QLineEdit;
    syntaxComboBox = new QComboBox;
    syntaxComboBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxComboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxComboBox->addItem(tr("Fixed string"), QRegExp::FixedString);

    filterLabel = new QLabel(tr("&Filter: "));
    filterLabel->setBuddy(filterLineEdit);
    patternLabel = new QLabel(tr("&Pattern Syntax: "));
    patternLabel->setBuddy(syntaxComboBox);

    connect(filterLineEdit, &QLineEdit::textChanged, this, &ColorNamesDialog::reapplyFilter);
    connect(syntaxComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
        this, &ColorNamesDialog::reapplyFilter);

    auto *gridLayout = new QGridLayout;
    gridLayout->addWidget(filterLabel, 0, 0);
    gridLayout->addWidget(filterLineEdit, 0, 1);
    gridLayout->addWidget(patternLabel, 1, 0);
    gridLayout->addWidget(syntaxComboBox, 1, 1);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listView);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
}

void ColorNamesDialog::reapplyFilter() {
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
            syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
    QRegExp regExp(filterLineEdit->text(), Qt::CaseInsensitive, syntax);
    proxyModel->setFilterRegExp(regExp);
}