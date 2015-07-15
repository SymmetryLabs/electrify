#ifndef COMPONENTGRIDITEMQT_H
#define COMPONENTGRIDITEMQT_H

#include <QWidget>

#include "component.h"

namespace Ui {
class ComponentGridItemQt;
}

class ComponentGridItemQt : public QWidget
{
  Q_OBJECT

public:
  ComponentGridItemQt(std::unique_ptr<Component> component, QWidget *parent = 0);
  ~ComponentGridItemQt();

private:
  Ui::ComponentGridItemQt* ui;

  std::unique_ptr<Component> component;
};

#endif // COMPONENTGRIDITEMQT_H
