#include <QtGui/QApplication>
#include "mainwindow.h"
#include "iterator"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int i1=23, i2=24;
    std::swap(i1,i2);
    qDebug()<<i1<<"  "<<i2;
    std::pair<int, int> p = std::pair<int, int>(1,3);
    qDebug()<<p.first<<"  "<<p.second;
    return a.exec();
}
