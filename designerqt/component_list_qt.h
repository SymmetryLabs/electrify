#ifndef COMPONENTLISTQT_H
#define COMPONENTLISTQT_H

#include "globals.h"

#include "component_registrar.h"

#include <QListWidget>

class ComponentListQt : public QListWidget
{
public:
  ComponentListQt(QWidget *parent = 0);

  ComponentRegistrar componentRegistrar;
};

#endif // COMPONENTLISTQT_H
