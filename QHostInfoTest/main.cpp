#include "qhostinfotest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHostInfoTest w;
    w.show();

    return a.exec();
}
