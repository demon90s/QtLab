#include "simplechatserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleChatServer w;
    w.show();

    return a.exec();
}
