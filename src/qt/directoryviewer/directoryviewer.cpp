#include "directoryviewer.h"

#include <QPushButton>
#include <QDirModel>
#include <QTreeView>
#include <QHeaderView>
#include <QDir>
#include <QLayout>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>

DirectoryViewer::DirectoryViewer(QWidget *parent) 
    : QDialog(parent) {
    model = new QDirModel;
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    treeView = new QTreeView;
    treeView->setModel(model);
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);
    treeView->header()->setSectionsClickable(true);

    QModelIndex index = model->index(QDir::currentPath());
    treeView->expand(index);
    treeView->scrollTo(index);
    treeView->resizeColumnToContents(0);

    createButton = new QPushButton(tr("&Create Directory"));
    removeButton = new QPushButton(tr("&Remove"));
    quitButton = new QPushButton(tr("&Quit"));

    connect(createButton, &QPushButton::clicked, this, &DirectoryViewer::create);
    connect(removeButton, &QPushButton::clicked, this, &DirectoryViewer::remove);
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);

    auto *hLayout = new QHBoxLayout;
    hLayout->addWidget(createButton);
    hLayout->addWidget(removeButton);
    hLayout->addStretch();
    hLayout->addWidget(quitButton);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeView);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);
    setMinimumSize(900, 600);
}

void DirectoryViewer::create() {
    QModelIndex index = treeView->currentIndex();
    if(!index.isValid())
        return;
    
    QString dirName = QInputDialog::getText(this,
                        tr("Create Directory"),
                        tr("Directory Name"));

    if(!dirName.isEmpty()) {
        if(!model->mkdir(index, dirName).isValid())
            QMessageBox::information(this, tr("Create Directory"),
                tr("Failed to create the directory"));
    }
}

void DirectoryViewer::remove() {
    QModelIndex index = treeView->currentIndex();
    if(!index.isValid())
        return;
    
    bool ok;
    if(model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if(!ok) {
        QMessageBox::information(this, tr("Remove"),
                tr("Failed to remove %1").arg(model->fileName(index)));
    }
}
