#include "link.h"
#include "node.h"
#include "window.h"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QList>
#include <QClipboard>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QColorDialog>

DiagramWindow::DiagramWindow() {
    scene = new QGraphicsScene(0, 0, 600, 500);
    view = new QGraphicsView;
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);
    minZ = 0;
    maxZ = 0;
    seqNumber = 0;
    createActions();
    createMenus();
    createToolBars();
    connect(scene, &QGraphicsScene::selectionChanged, this, &DiagramWindow::updateActions);
    setWindowTitle(tr("Diagram"));
    updateActions();
}

void DiagramWindow::addNode() {
    Node *node = new Node;
    node->setText(tr("Node %1").arg(seqNumber+1));
    setupNode(node);
}

void DiagramWindow::setupNode(Node *node) {
    node->setPos(QPoint(80 + (100 * (seqNumber % 5)),
                        80 + (50 * ((seqNumber / 5) % 7))));
    scene->addItem(node);
    ++seqNumber;

    scene->clearSelection();
    node->setSelected(true);
    bringToFront();
}

void DiagramWindow::bringToFront() {
    ++maxZ;
    setZValue(maxZ);
}

void DiagramWindow::sendToBack() {
    --minZ;
    setZValue(minZ);
}

void DiagramWindow::setZValue(int z) {
    Node *node = selectedNode();
    if(node)
        node->setZValue(z);
}

Node *DiagramWindow::selectedNode() const {
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1) {
        return dynamic_cast<Node *>(items.first());
    } else {
        return nullptr;
    }
}

Link *DiagramWindow::selectedLink() const {
    QList<QGraphicsItem *> items = scene->selectedItems();
    if(items.count() == 1) {
        return dynamic_cast<Link *>(items.first());
    } else {
        return nullptr;
    }
}

void DiagramWindow::addLink() {
    NodePair nodes = selectedNodePair();
    if (nodes == NodePair())
        return;
    Link *link = new Link(nodes.first, nodes.second);
    scene->addItem(link);
}

DiagramWindow::NodePair DiagramWindow::selectedNodePair() const {
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 2) {
        Node *first = dynamic_cast<Node *>(items.first());
        Node *second = dynamic_cast<Node *>(items.last());
        if (first && second)
            return NodePair(first, second);
    }
    return NodePair();
}

void DiagramWindow::del() {
    QList<QGraphicsItem *> items = scene->selectedItems();
    QMutableListIterator<QGraphicsItem *> i(items);
    while (i.hasNext()) {
        Link *link = dynamic_cast<Link *>(i.next());
        if (link) {
            delete link;
            i.remove();
        }
    }
    qDeleteAll(items);
}

void DiagramWindow::properties() {
    Node *node = selectedNode();
    Link *link = selectedLink();
    if (node) {
        //PropertiesDialog dialog(node, this);
        //dialog.exec();
    } else if (link) {
        QColor color = QColorDialog::getColor(link->color(), this);
        if (color.isValid())
        link->setColor(color);
    }
}

void DiagramWindow::cut() {
    Node *node = selectedNode();
    if (!node)
        return;
    copy();
    delete node;
}

void DiagramWindow::copy()
{
    Node *node = selectedNode();
    if (!node)
        return;
    QString str = QString("Node %1 %2 %3 %4")
                    .arg(node->textColor().name())
                    .arg(node->outlineColor().name())
                    .arg(node->backgroundColor().name())
                    .arg(node->text());
    QApplication::clipboard()->setText(str);
}

void DiagramWindow::paste() {
    QString str = QApplication::clipboard()->text();
    QStringList parts = str.split(" ");
    if (parts.count() >= 5 && parts.first() == "Node") {
        Node *node = new Node;
        node->setText(QStringList(parts.mid(4)).join(" "));
        node->setTextColor(QColor(parts[1]));
        node->setOutlineColor(QColor(parts[2]));
        node->setBackgroundColor(QColor(parts[3]));
        setupNode(node);
    }
}

void DiagramWindow::updateActions() {
    bool hasSelection = !scene->selectedItems().isEmpty();
    bool isNode = (selectedNode() != 0);
    bool isNodePair = (selectedNodePair() != NodePair());

    cutAction->setEnabled(isNode);
    copyAction->setEnabled(isNode);
    newLinkAction->setEnabled(isNodePair);
    deleteAction->setEnabled(hasSelection);
    bringToFrontAction->setEnabled(isNode);
    sendToBackAction->setEnabled(isNode);
    propertiesAction->setEnabled(isNode);
    foreach (QAction *action, view->actions())
        view->removeAction(action);

    foreach (QAction *action, editMenu->actions()) {
        if (action->isEnabled())
            view->addAction(action);
    }
}

void DiagramWindow::createActions() {
    newNodeAction = new QAction(tr("&Node"), this);
    newNodeAction->setIcon(QIcon(":/images/node.png"));
    newNodeAction->setShortcut(QKeySequence::New);
    connect(newNodeAction, &QAction::triggered, this, &DiagramWindow::addNode);

    newLinkAction = new QAction(tr("&Link"), this);
    newLinkAction->setIcon(QIcon(":/images/link.png"));
    connect(newLinkAction, &QAction::triggered, this, &DiagramWindow::addLink);

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/images/delete.png"));
    connect(deleteAction, &QAction::triggered, this, &DiagramWindow::del);

    sendToBackAction = new QAction(tr("Send To Back"), this);
    sendToBackAction->setIcon(QIcon(":/images/send-to-back.svg"));
    connect(sendToBackAction, &QAction::triggered, this, &DiagramWindow::sendToBack);

    bringToFrontAction = new QAction(tr("Bring To Front"));
    bringToFrontAction->setIcon(QIcon(":/images/bring-forward.png"));
    connect(bringToFrontAction, &QAction::triggered, this, &DiagramWindow::bringToFront);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    connect(cutAction, &QAction::triggered, this, &DiagramWindow::cut);

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    connect(copyAction, &QAction::triggered, this, &DiagramWindow::copy);

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    connect(pasteAction, &QAction::triggered, this, &DiagramWindow::paste);

    propertiesAction = new QAction(tr("Properties"), this);
    connect(propertiesAction, &QAction::triggered, this, &DiagramWindow::properties);
}

void DiagramWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newNodeAction);
    fileMenu->addAction(newLinkAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(propertiesAction);
    fileMenu->addSeparator();

    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
}

void DiagramWindow::createToolBars() {
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newNodeAction);
    fileToolBar->addAction(newLinkAction);
    fileToolBar->addAction(deleteAction);
    fileToolBar->addSeparator();

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(bringToFrontAction);
    editToolBar->addAction(sendToBackAction);
}