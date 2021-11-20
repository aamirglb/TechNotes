#include <QListWidget>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>

#include "preferencedialog.h"

PreferenceDialog::PreferenceDialog(QDialog *parent)
    : QDialog(parent) {
    listWidget = new QListWidget;
    listWidget->addItem(tr("Appearance"));
    listWidget->addItem(tr("Web Browser"));
    listWidget->addItem(tr("Mail & News"));
    listWidget->addItem(tr("Advanced"));
    listWidget->setMinimumWidth(listWidget->sizeHintForColumn(0));
    // listWidget->setStretchFactor(1, 1);

    appearancePage = new AppearancePage;
    webBrowserPage = new WebBroswerPage;
    mailAndNewsPage = new MailAndNewsPage;
    advancedPage = new AdvancedPage;

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(appearancePage);
    stackedLayout->addWidget(webBrowserPage);
    stackedLayout->addWidget(mailAndNewsPage);
    stackedLayout->addWidget(advancedPage);
    // stackedLayout->setStretchFactor(1, 2);
    connect(listWidget, &QListWidget::currentRowChanged, stackedLayout, &QStackedLayout::setCurrentIndex);
    listWidget->setCurrentRow(0);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(listWidget, 0, 0, 1, 1);
    mainLayout->addLayout(stackedLayout, 0, 1, 1, 3);
    mainLayout->addWidget(buttonBox, 1, 1, 1, 1);
    setLayout(mainLayout);
}

AppearancePage::AppearancePage(QWidget *parent)
    : QWidget(parent) {
    label = new QLabel("<h1>Appearnce Page</h1>");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

WebBroswerPage::WebBroswerPage(QWidget *parent)
    : QWidget(parent) {
    label = new QLabel("<h1>Web Browser</h1>");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

MailAndNewsPage::MailAndNewsPage(QWidget *parent)
    : QWidget(parent) {
    label = new QLabel("<h1>Mail And News Page</h1>");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

AdvancedPage::AdvancedPage(QWidget *parent)
    : QWidget(parent) {
    label = new QLabel("<h1><font color='red'>Advance Page</font></h1>");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}