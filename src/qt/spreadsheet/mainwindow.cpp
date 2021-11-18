#include <QtWidgets>
#include <QFileDialog>
#include <QAction>
#include <QSettings>

#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h"

MainWindow::MainWindow() {
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBar();
    createStatusBar();

    readSettings();

    findDialog = nullptr;

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
}

void MainWindow::createActions() {
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open existing spreadsheet"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current spreadsheet"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveAsAction = new QAction(tr("Save As"), this);
    saveAsAction->setIcon(QIcon(":/images/saveas.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save current spreadsheet"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);

    for(auto i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the applicaiton"));
    exitAction->setIcon(QIcon(":/images/exit.png"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut current selection"));
    cutAction->setIcon(QIcon(":/images/cut.png"));
    connect(cutAction, &QAction::triggered, spreadsheet, &Spreadsheet::cut);

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy current selection"));
    copyAction->setIcon(QIcon(":/images/copy.png"));
    connect(copyAction, &QAction::triggered, spreadsheet, &Spreadsheet::copy);

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste current selection"));
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    connect(pasteAction, &QAction::triggered, spreadsheet, &Spreadsheet::paste);

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete current selection"));
    deleteAction->setIcon(QIcon(":/images/del.png"));
    connect(deleteAction, &QAction::triggered, spreadsheet, &Spreadsheet::del);

    selectRowAction = new QAction(tr("&Row"), this);
    selectRowAction->setStatusTip(tr("Select current row"));
    selectRowAction->setIcon(QIcon(":/images/row_select.png"));
    connect(selectRowAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectCurrentRow);

    selectColumnAction = new QAction(tr("&Column"), this);
    selectColumnAction->setStatusTip(tr("Select current column"));
    selectColumnAction->setIcon(QIcon(":/images/column_select.png"));
    connect(selectColumnAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectCurrentColumn);

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setIcon(QIcon(":/images/all_select.png"));
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, &QAction::triggered, spreadsheet, &Spreadsheet::selectAll);

    findAction = new QAction(tr("&Find"), this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find value"));
    findAction->setIcon(QIcon(":/images/find.png"));
    connect(findAction, &QAction::triggered, this, &MainWindow::find); 

    goToCellAction = new QAction(tr("&Go to Cell"), this);
    goToCellAction->setStatusTip(tr("Find a value"));
    goToCellAction->setIcon(QIcon(":/images/goto.png"));
    connect(goToCellAction, &QAction::triggered, this, &MainWindow::goToCell);

    // Tool
    reCalculateAction = new QAction(tr("&Recalculate"), this);
    reCalculateAction->setStatusTip(tr("Recalculate cells"));
    reCalculateAction->setIcon(QIcon(":/images/recalc.png"));
    connect(reCalculateAction, &QAction::triggered, spreadsheet, &Spreadsheet::recalculate);

    sortAction = new QAction(tr("&Sort"), this);
    sortAction->setIcon(QIcon(":/images/sort.png"));
    connect(sortAction, &QAction::triggered, this, &MainWindow::sort);

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, &QAction::toggled, spreadsheet, &Spreadsheet::setShowGrid);

    autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalcAction->setCheckable(true);
    autoRecalcAction->setStatusTip(tr("Enable/disable auto recalculate"));
    connect(autoRecalcAction, &QAction::toggled, spreadsheet, &Spreadsheet::setAutoRecalculate);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About spreadsheet application"));
    aboutAction->setIcon(QIcon(":/images/icon.png"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for(auto i = 0; i < MaxRecentFiles; ++i) {
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->setIcon(QIcon(":/images/select.png"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(reCalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu() {
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBar() {
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar() {
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spreadsheet, &Spreadsheet::currentCellChanged, this, &MainWindow::updateStatusBar);
    connect(spreadsheet, &Spreadsheet::modified, this, &MainWindow::spreadsheetModified);
    updateStatusBar();
}

void MainWindow::updateStatusBar() {
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified() {
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile() {
    if(okToContinue()) {
        spreadsheet->clear();
        setCurrentFile("");
    }
}

bool MainWindow::okToContinue() {
    if(isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
            tr("The document has been modified.\n"
            "Do you want to save your changes?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if(r == QMessageBox::Yes) {
            return save();
        } else if(r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::open() {
    if(okToContinue()) {
        QString filename = QFileDialog::getOpenFileName(this, 
            tr("Open Spreadsheet"), ".", tr("Spreadsheet files (*.sp"));
        
        if(!filename.isEmpty()) {
            loadFile(filename);
        }
    }
}

bool MainWindow::loadFile(const QString &filename) {
    if(!spreadsheet->readFile(filename)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(filename);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save() {
    if(curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveFile(const QString &filename) {
    if(!spreadsheet->writeFile(filename)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(filename);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs() {
    QString filename = QFileDialog::getSaveFileName(this, 
        tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp"));

    if(filename.isEmpty())
        return false;
    return saveFile(filename);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::setCurrentFile(const QString &filename) {
    curFile = filename;
    setWindowModified(false);
    QString shownName = tr("Untitled");

    if(!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullname) {
    return QFileInfo(fullname).fileName();
}

void MainWindow::updateRecentFileActions() {
    QMutableStringListIterator i(recentFiles);
    while(i.hasNext()) {
        if(!QFile::exists(i.next()))
            i.remove();
    }

    for(int j = 0; j < MaxRecentFiles; ++j) {
        if( j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile() {
    if(okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find() {
    if(!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, &FindDialog::findNext, spreadsheet, &Spreadsheet::findNext);
        connect(findDialog, &FindDialog::findPrevious, spreadsheet, &Spreadsheet::findPrevious);

        findDialog->show();
        findDialog->raise();
        findDialog->activateWindow();
    }
}

void MainWindow::goToCell() {
    GoToCellDialog dialog(this);
    if(dialog.exec()) {
        QString str = dialog.lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt()-1, str[0].unicode() - 'A');
    }
}

void MainWindow::sort() {
    SortDialog dialog(this);

    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());
    if(dialog.exec()) {
        SpreadsheetCompare compare;
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;

        compare.ascending[0] = (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] = (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] = (dialog.tertiaryOrderCombo->currentIndex() == 0);

        spreadsheet->sort(compare);
    }
}

// void MainWindow::sort() {
//     SortDialog dialog(this);
//     QTableWidgetSelectionRange range = spreadsheet->selectedRange();
//     dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

//     if(dialog.exec())
//         spreadsheet->performSort(dialog.comparisonObject());
// }

void MainWindow::about() {
    QMessageBox::about(this, tr("About Spreadsheet"),
        tr("<h2>Spreadsheet 1.0</h2>"
        "<p>Copyright &copy; 2021 Software Inc."
        "<p>Spreadsheet is a small application that "
        "demonstrates QAction, QMainWindow, QMenuBar, "
        "QStatusBar, QTableWidget, QToolBar and many other "
        "Qt classes."
        ));
}

void MainWindow::writeSettings() {
    QSettings settings("Software Inc.", "Spreadsheet");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
}

void MainWindow::readSettings() {
    QSettings settings("Software Inc.", "Spreadsheet");
    restoreGeometry(settings.value("geometry").toByteArray());
    
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}