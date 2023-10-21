#pragma once
#include <QtWidgets>
#include <QSqlTableModel>
#include <QTableView>
#include <QComboBox>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

private:
    void indexChanged(int index);

private:
    QSqlTableModel *m_model;
    QTableView *m_view;
    QComboBox *m_tableNames;
    QSortFilterProxyModel* m_proxy;
};