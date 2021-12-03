#include <QDialog>

class QDirModel;
class QTreeView;
class QPushButton;

class DirectoryViewer : public QDialog {
    Q_OBJECT
public:
    DirectoryViewer(QWidget *parent = nullptr);

public slots:
    void create();
    void remove();

private:
    QDirModel *model;
    QTreeView *treeView;

    QPushButton *createButton;
    QPushButton *removeButton;
    QPushButton *quitButton;
};