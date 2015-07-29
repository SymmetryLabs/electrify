#ifndef COMPONENTGRIDQT_H
#define COMPONENTGRIDQT_H

#include "globals.h"

#include "component_grid.h"

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragMoveEvent>

namespace Ui {
class ComponentGridQt;
}

class ComponentGridQt : public QWidget
{
  Q_OBJECT

  USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
  explicit ComponentGridQt(QWidget* parent = 0);
  ~ComponentGridQt();

  void init(ComponentGrid* componentGrid);
  void setComponentGrid(ComponentGrid* componentGrid);

private:
  Ui::ComponentGridQt* ui;

  VarSignalT<ComponentGrid*> componentGrid = MakeVar<EngineUiDomain, ComponentGrid*>(nullptr);
  EventsT<pair<size_t, reference_wrapper<shared_ptr<ComponentGridItem>>>> componentGridAddedItem;
  EventsT<pair<size_t, shared_ptr<ComponentGridItem>>> componentGridRemovedItem;

  void addWithGridItem(ComponentGridItem* gridItem);
  void removeWithGridItem(ComponentGridItem* gridItem);
  void removeAllGridItems();

  void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
//  void dragMoveEvent(QDragMoveEvent* event) Q_DECL_OVERRIDE;
  void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;
//  void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
};

#endif // COMPONENTGRIDQT_H
