#include <QApplication>
#include <QProgressDialog>
#include <QTimer>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *timer = new QTimer;
    int32_t percent {};
    auto *dialog = new QProgressDialog;
    dialog->setRange(0, 200);

    auto updateStatus = [&]() {
        percent++;
        dialog->setValue(percent);
        dialog->setLabelText(QWidget::tr("Completed %1").arg(percent));
        if(dialog->wasCanceled())
            qApp->quit();
        if(percent >= 200)
            qApp->quit();
    };

    QObject::connect(timer, &QTimer::timeout, updateStatus);
    //dialog->show();
    timer->start(50);
    return app.exec();

}