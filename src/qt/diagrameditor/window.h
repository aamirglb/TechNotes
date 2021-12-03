#pragma once
#include <QMainWindow>

class Node;
class Link;
class QMenu;
class QAction;
class QToolBar;
class QGraphicsScene;
class QGraphicsView;

class DiagramWindow : public QMainWindow {
    Q_OBJECT
public:
    DiagramWindow();

private slots:
    void addNode();
    void addLink();
    void del();
    void cut();
    void copy();
    void paste();
    void bringToFront();
    void sendToBack();
    void properties();
    void updateActions();
private:
    using NodePair = QPair<Node *, Node *>;
    void createActions();
    void createMenus();
    void createToolBars();
    void setZValue(int z);
    void setupNode(Node *node);
    Node *selectedNode() const;
    Link *selectedLink() const;
    NodePair selectedNodePair() const;

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newNodeAction;
    QAction *newLinkAction;
    QAction *deleteAction;
    QAction *exitAction;

    QAction *sendToBackAction;
    QAction *bringToFrontAction;

    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *propertiesAction;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QGraphicsScene *scene;
    QGraphicsView *view;
    int minZ;
    int maxZ;
    int seqNumber;
};