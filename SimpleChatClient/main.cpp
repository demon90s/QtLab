#include "simplechatclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleChatClient w;
    w.show();

    return a.exec();
}
