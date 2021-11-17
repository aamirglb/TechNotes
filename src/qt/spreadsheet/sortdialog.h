#pragma once

#include <QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog, public Ui::SortDialog {
    Q_OBJECT

public:
    SortDialog(QWidget *parent = nullptr);
    void setColumnRange(QChar first, QChar last);
};
