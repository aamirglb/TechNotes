#pragma once
#include <QWidget>

class QLabel;
class QLineEdit;
class QTableWidget;
class QCheckBox;
class QPushButton;


class FindFileDialog : public QWidget {
    Q_OBJECT

public:
    FindFileDialog(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *evnet) override;

private:
    QLabel  *namedLabel;
    QLineEdit *namedLineEdit;
    QLabel    *lookInLabel;
    QLineEdit  *lookInLineEdit;
    QCheckBox  *subfoldersCheckBox;
    QTableWidget *tableWidget;
    QLabel       *messageLabel;
    QPushButton  *findButton;
    QPushButton  *stopButton;
    QPushButton  *closeButton;
    QPushButton  *helpButton;
};