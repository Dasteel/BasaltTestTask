#include <QCoreApplication>
#include <QDebug>
#include "lib/MyLib.h"




int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    MyLib myLib(QString("p10"),QString("sisyphus"),QString("json"));
    myLib.compare_branches();





    return a.exec();
}
