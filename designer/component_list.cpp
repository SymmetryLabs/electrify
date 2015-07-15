#include "component_list.h"

ComponentList::ComponentList(QWidget *parent) : QListWidget(parent)
{
    for (auto componentName : componentRegistrar.getAvailableComponents()) {
        addItem(QString::fromStdString(componentName));
    }
}

