#include <QSplitter>
#include <QTextEdit>
#include <QTreeWidget>
#include <QSettings>
#include <QCloseEvent>

#include "mailclient.h"

MailClient::MailClient(QMainWindow *parent)
    : QMainWindow(parent) {

    messageTreeWidget = new QTreeWidget;
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    folderTreeWidget = new QTreeWidget;

    rightSplitter = new QSplitter(Qt::Vertical);
    rightSplitter->addWidget(messageTreeWidget);
    rightSplitter->addWidget(textEdit);
    rightSplitter->setStretchFactor(1, 1);

    mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(folderTreeWidget);
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(1, 1);
    
    setCentralWidget(mainSplitter);
    setWindowTitle(tr("Mail Client"));
    readSettings();
}

void MailClient::writeSettings() {
    QSettings settings("Software Inc.", "Mail Client");
    settings.beginGroup("mainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("mainSplitter", mainSplitter->saveState());
    settings.setValue("rightSplitter", rightSplitter->saveState());
    settings.endGroup();
}

void MailClient::readSettings() {
    QSettings settings("Software Inc.", "Mail Client");
    settings.beginGroup("mainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
    rightSplitter->restoreState(settings.value("rightSplitter").toByteArray());
    settings.endGroup();
}

void MailClient::closeEvent(QCloseEvent *event) {
    writeSettings();
    event->accept();
}