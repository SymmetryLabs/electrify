#include "component_list_qt.h"

ComponentListQt::ComponentListQt(QWidget *parent) : QListWidget(parent)
{
  for (auto componentName : componentRegistrar.getAvailableComponents()) {
    addItem(QString::fromStdString(componentName));
  }
}

