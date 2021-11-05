#include "widget.h"
#include "qtclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtClient m;
    m.show();
    Widget w;
    w.show();
    return a.exec();
}
