#include "component_grid_qt.h"
#include "ui_component_grid_qt.h"

#include "component_grid_item_qt.h"

#include <QtDebug>
#include <QMimeData>

ComponentGridQt::ComponentGridQt(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ComponentGridQt)
{
  ui->setupUi(this);
}

ComponentGridQt::~ComponentGridQt()
{
  delete ui;
}

void ComponentGridQt::init(ComponentGrid* componentGrid_)
{
  Observe(componentGrid, [this] (ComponentGrid* componentGrid) {
    removeAllGridItems();
    if (componentGrid != nullptr) {
      for (const shared_ptr<ComponentGridItem>& gridItem : componentGrid->gridItems) {
        addWithGridItem(gridItem.get());
      }
    }
  });

  this->componentGrid <<= componentGrid_;

  componentGridAddedItem = REACTIVE_PTR(componentGrid, gridItems.valueAdded);
  componentGridRemovedItem = REACTIVE_PTR(componentGrid, gridItems.valueRemoved);

  Observe(componentGridAddedItem, [&] (const pair<size_t, reference_wrapper<shared_ptr<ComponentGridItem>>>& p) {
    addWithGridItem(p.second.get().get());
  });

  Observe(componentGridRemovedItem, [&] (const pair<size_t, shared_ptr<ComponentGridItem>>& p) {
    removeWithGridItem(p.second.get());
  });
}

void ComponentGridQt::setComponentGrid(ComponentGrid* componentGrid_)
{
  this->componentGrid <<= componentGrid_;
}

void ComponentGridQt::addWithGridItem(ComponentGridItem* gridItem)
{
  auto gridItemQt = new ComponentGridItemQt(gridItem, this);
  gridItemQt->show();
}

void ComponentGridQt::removeWithGridItem(ComponentGridItem* gridItem)
{
}

void ComponentGridQt::removeAllGridItems()
{
}

void ComponentGridQt::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
    event->acceptProposedAction();
  }
}

void ComponentGridQt::dropEvent(QDropEvent *event)
{
  QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
  QDataStream stream(&encoded, QIODevice::ReadOnly);

  while (!stream.atEnd())
  {
    int row, col;
    QMap<int,  QVariant> roleDataMap;
    stream >> row >> col >> roleDataMap;

    std::string name = roleDataMap[0].toString().toStdString();

    componentGrid.Value()->addComponent(name, event->pos().x(), event->pos().y());
  }

  event->acceptProposedAction();
}
