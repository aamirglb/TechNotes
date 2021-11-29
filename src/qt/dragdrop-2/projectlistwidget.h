#include <QListWidget>
#include <QPoint>

class ProjectListWidget : public QListWidget {
    Q_OBJECT

public:
    ProjectListWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

public slots:
    void moveItem(ProjectListWidget *dst);

private:
    void performDrag();
    QPoint startPos;
};