#include <QDialog>
#include <QStringList>

class QStringListModel;
class QListView;
class QPushButton;

class TeamLeadersDialog : public QDialog {
    Q_OBJECT
public:
    TeamLeadersDialog(const QStringList &leaders, QWidget *parent = nullptr);

public slots:
    void insert();
    void del();
    void done();
    void cancel();
    QStringList leaders() const;

private:
    void updateDeleteButton();

private:
    QStringListModel *model;
    QListView *listView;

    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
};