#include "designer_window_qt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DesignerWindowQt w;
  w.show();

  return a.exec();
}
