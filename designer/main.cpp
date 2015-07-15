#include "designer_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesignerWindow w;
    w.show();

    return a.exec();
}
