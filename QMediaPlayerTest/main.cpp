#include "qmediaplayertest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMediaPlayerTest w;
    w.show();

    return a.exec();
}
