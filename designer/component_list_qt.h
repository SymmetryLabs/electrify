#ifndef COMPONENTLISTQT_H
#define COMPONENTLISTQT_H

#include <QListWidget>

#include "component_registrar.h"

class ComponentListQt : public QListWidget
{
public:
  ComponentListQt(QWidget *parent = 0);

  ComponentRegistrar componentRegistrar;
};

#endif // COMPONENTLISTQT_H
