#include "circuitos.h"
#include <QApplication>


Circuitos *pt_w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Circuitos w;
    pt_w = &w;
    w.show();

    return a.exec();
}
