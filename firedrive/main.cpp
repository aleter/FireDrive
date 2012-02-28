#include <QtGui/QApplication>
#include "firedrive.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FireDrive w;
    w._init();
    w.show();

    return a.exec();
}
