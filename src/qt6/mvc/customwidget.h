#pragma once
#include <QtWidgets>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

private:
    void textChanged(const QString& text);
    void addRow();
    void removeRow();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QListView *m_View;
    QStringListModel *m_Model;
    QLineEdit *m_Text;
    QPushButton *m_AddButton;
    QPushButton *m_RemoveButton;
    // QItemSelectionModel *m_SelectionModel;
};