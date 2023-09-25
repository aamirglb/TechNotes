#pragma once
#include <QtWidgets>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

private slots:
    void itemClicked(QListWidgetItem* item);
    void updateItem();

private:
    QListWidget *m_widget;
    QLineEdit *m_edit;
    QPushButton *m_button;
};