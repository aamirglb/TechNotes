#include <QDialog>
#include <QWidget>

class QListWidget;
class QStackedLayout;
class QLabel;
class QDialogButtonBox;

class AppearancePage;
class WebBroswerPage;
class MailAndNewsPage;
class AdvancedPage;

class PreferenceDialog : public QDialog {
    Q_OBJECT
public:
    PreferenceDialog(QDialog *parent = nullptr);

private:
    QListWidget *listWidget;
    QStackedLayout *stackedLayout;
    AppearancePage *appearancePage;
    WebBroswerPage *webBrowserPage;
    MailAndNewsPage *mailAndNewsPage;
    AdvancedPage *advancedPage;
    QDialogButtonBox *buttonBox;
};

class AppearancePage : public QWidget {
public:
    AppearancePage(QWidget *parent = nullptr);

private:
    QLabel *label;
};

class WebBroswerPage : public QWidget {
public:
    WebBroswerPage(QWidget *parent = nullptr);

private:
    QLabel *label;
};

class MailAndNewsPage : public QWidget {
public:
    MailAndNewsPage(QWidget *parent = nullptr);

private:
    QLabel *label;
};

class AdvancedPage : public QWidget {
public:
    AdvancedPage(QWidget *parent = nullptr);

private:
    QLabel *label;
};