#include "dialog.h"

#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QLayout>
#include <QDebug>

TeamLeadersDialog::TeamLeadersDialog(const QStringList &leaders, QWidget *parent) 
    : QDialog(parent) {
    model = new QStringListModel(this);
    model->setStringList(leaders);

    listView = new QListView;
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | 
                              QAbstractItemView::DoubleClicked);

    insertButton = new QPushButton(tr("Insert"));
    deleteButton = new QPushButton(tr("Delete"));
    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    connect(insertButton, &QPushButton::clicked, this, &TeamLeadersDialog::insert);
    connect(deleteButton, &QPushButton::clicked, this, &TeamLeadersDialog::del);
    connect(okButton, &QPushButton::clicked, this, &TeamLeadersDialog::done);
    connect(cancelButton, &QPushButton::clicked, this, &TeamLeadersDialog::cancel);

    auto *hLayout = new QHBoxLayout;
    hLayout->addWidget(insertButton);
    hLayout->addWidget(deleteButton);
    hLayout->addWidget(okButton);
    hLayout->addWidget(cancelButton);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listView);
    mainLayout->addLayout(hLayout);

    this->setLayout(mainLayout);
}

void TeamLeadersDialog::insert() {
    int row = 0;
    if(model->rowCount() > 0) {
        row = listView->currentIndex().row();
    }
    
    model->insertRows(row, 1);

    QModelIndex index = model->index(row);
    model->setData(index, QString("New Leader"));
    listView->setCurrentIndex(index);
    listView->edit(index);
    updateDeleteButton();
}

void TeamLeadersDialog::del() {
    model->removeRows(listView->currentIndex().row(), 1);
    updateDeleteButton();
}

void TeamLeadersDialog::done() {
    qDebug() << leaders();
    QDialog::done(QDialog::Accepted);
}

void TeamLeadersDialog::cancel() {
    QDialog::done(QDialog::Rejected);
}

void TeamLeadersDialog::updateDeleteButton() {
    if(model->rowCount() > 0) {
        deleteButton->setEnabled(true);
    } else {
        deleteButton->setEnabled(false);
    }
}


QStringList TeamLeadersDialog::leaders() const {
    return model->stringList();
}