#include <QApplication>
#include <QTextEdit>
#include <QSplitter>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTextEdit *editor1 = new QTextEdit;
    QTextEdit *editor2 = new QTextEdit;
    QTextEdit *editor3 = new QTextEdit;

    QSplitter splitter(Qt::Horizontal);
    splitter.addWidget(editor1);
    splitter.addWidget(editor2);
    splitter.addWidget(editor3);

    QString text = "The child widgets of a QSplitter are automatically placed "
    "side by side (or one below the other) in the order in which they are created, "
    "with splitter bars between adjacent widgets.";
    editor1->setText(text);
    editor2->setText(text);
    editor3->setText(text);

    splitter.show();
    return app.exec();
}