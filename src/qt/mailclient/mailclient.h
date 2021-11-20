#pragma once

#include <QMainWindow>

class QSplitter;
class QTreeWidget;
class QTextEdit;

class MailClient : public QMainWindow {
public:
    MailClient(QMainWindow *parent = nullptr);

private:
    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event) override;
    
private:
    QSplitter *rightSplitter;
    QTreeWidget *folderTreeWidget;
    QTreeWidget *messageTreeWidget;
    QSplitter *mainSplitter;
    QTextEdit *textEdit;
};