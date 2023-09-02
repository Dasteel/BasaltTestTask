#include <QCoreApplication>

#include "MyLib.h"




int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    MyLib myLib(QString("sisyphus"),QString("p10"),QString("json"));
    myLib.compare_branches();
    myLib.compare_version();
    exit(1);





    return a.exec();
}
