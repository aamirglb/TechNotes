#include "projectlistwidget.h"

#include <QMouseEvent>
#include <QMimeData>
#include <QListWidgetItem>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QApplication>
#include <QDebug>

ProjectListWidget::ProjectListWidget(QWidget *parent)
    : QListWidget(parent) {
    setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if(distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListWidget::mouseMoveEvent(event);
}

void ProjectListWidget::moveItem(ProjectListWidget *dst) {
    if(dst == this)
        return;

    auto *item = currentItem();
    if(item) {
        new QListWidgetItem(item->text(), dst);
        delete takeItem(this->row(item));
    }
}

void ProjectListWidget::performDrag() {
    qDebug() << "Performing drag";
    QListWidgetItem *item = currentItem();
    if(item) {
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());
        qDebug() << "Drag Text:" << item->text();

        auto *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(":/images/person2.png"));
        if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
            delete item;
    }
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event) {
    auto *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event) {
    auto *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent *event) {
    auto *source = qobject_cast<ProjectListWidget *>(event->source());
    if(source && source != this) {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}