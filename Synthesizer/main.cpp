#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(pathReader(argv));
    w.setFixedSize(1418, 353);
    w.show();

    return a.exec();
}
