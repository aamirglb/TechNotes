#include "mainwindow.h"

#include <QTextEdit>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QTextStream>
#include <QMimeData>

MainWindow::MainWindow() {
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if(event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
    if(fileName.isEmpty())
        return;

    if(readFile(fileName))
        setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("Drag File")));
}

bool MainWindow::readFile(const QString &fileName) {
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream txtStream(&file);
    textEdit->setText(txtStream.readAll());
    file.close();
    return true;
}