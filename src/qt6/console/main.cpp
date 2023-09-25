#include <QtCore>
// #include <QConsoleApplication>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QDir>

QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    QString s1("Abu Dhabi");
    QString s2("Dubai");

    QString s = s1 + " " + s2 + "!!";
    cout << s << Qt::endl;

    QString s3("Hello");
    QString s4("Qt");
    QList<QString> list;

    list << s3 << s4;

    QListIterator<QString> itr(list);
    while(itr.hasNext()) {
        cout << itr.next();
        if(itr.hasNext()) {
            cout << ", ";
        }
    }
    cout << "!" << Qt::endl;

    // Read CSV file
    cout << "Current Working Directory: " << QDir::currentPath() << Qt::endl;
    QList<QStringList> data;
    QFile file("sample.csv");
    if( file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        // forever macro from Qt
        forever {
            QString line = stream.readLine();
            if(line.isNull()) break;
            if(line.isEmpty()) continue;

            QStringList row;
            foreach(const QString& cell, line.split(",")) {
                row.append(cell.trimmed());
                // cout << cell.trimmed() << " ";
            }
            data.append(row);

            for(int i = 0; i < row.length(); ++i)
            {
                cout << row[i] << "-";
            }
            cout << Qt::endl;
            // cout << row[row.length() - 1] << Qt::endl;
            // cout << data << Qt::endl;
        }
    } else {
        cout << "Unable to open sample.csv file" << Qt::endl;
    }
}