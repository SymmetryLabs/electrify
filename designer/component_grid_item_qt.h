#ifndef COMPONENTGRIDITEMQT_H
#define COMPONENTGRIDITEMQT_H

#include "blueprint_ui_globals.h"

#include "component_grid_item.h"
#include "observes.h"

#include <QWidget>

namespace Ui {
class ComponentGridItemQt;
}

class ComponentGridItemQt : public QWidget, public Observes<EngineUiDomain>
{
  Q_OBJECT

public:
  ComponentGridItemQt(ComponentGridItem* componentGridItem, QWidget* parent = 0);
  ~ComponentGridItemQt();

  ComponentGridItem* componentGridItem;

private:
  Ui::ComponentGridItemQt* ui;
};

#endif // COMPONENTGRIDITEMQT_H
