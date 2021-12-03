#include <QDialog>

class QStringListModel;
class QSortFilterProxyModel;
class QListView;
class QComboBox;
class QLineEdit;
class QLabel;

class ColorNamesDialog : public QDialog {
    Q_OBJECT
public:
    ColorNamesDialog(QWidget *parent = nullptr);

public slots:
    void reapplyFilter();

private:
    QStringListModel *sourceModel;
    QSortFilterProxyModel *proxyModel;
    QListView *listView;
    QComboBox *syntaxComboBox;
    QLineEdit *filterLineEdit;
    QLabel *filterLabel;
    QLabel *patternLabel;
};