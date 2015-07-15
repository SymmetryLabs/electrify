#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QListWidget>

#include "component_registrar.h"

class ComponentList : public QListWidget
{
public:
    ComponentList(QWidget *parent = 0);

    ComponentRegistrar componentRegistrar;
};

#endif // COMPONENTLIST_H
