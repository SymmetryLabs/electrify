#include "component_grid_qt.h"
#include "ui_component_grid_qt.h"

#include "component_grid_item_qt.h"

#include <QtDebug>
#include <QMimeData>
#include <QDrag>

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
  } else if (event->mimeData()->hasFormat("application/x-componentgriditem")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->ignore();
    }
  } else {
    event->ignore();
  }
}

void ComponentGridQt::dragMoveEvent(QDragMoveEvent* event)
{
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
    event->acceptProposedAction();
  } else if (event->mimeData()->hasFormat("application/x-componentgriditem")) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->ignore();
    }
  } else {
    event->ignore();
  }
}

void ComponentGridQt::dropEvent(QDropEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
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
  } else if (event->mimeData()->hasFormat("application/x-componentgriditem")) {
    const QMimeData* mime = event->mimeData();

    QByteArray itemData = mime->data("application/x-componentgriditem");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QString name;
    QPoint offset;
    dataStream >> name >> offset;

    ComponentGridItemQt* child = findChild<ComponentGridItemQt*>(name);
    if (!child) {
      event->ignore();
      return;
    }

    if (event->source() == this) {
      child->setPos(event->pos() - offset);

      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->ignore();
    }
  } else {
    event->ignore();
  }
}

void ComponentGridQt::mousePressEvent(QMouseEvent* event)
{
  QWidget* object = childAt(event->pos());
  if (!object)
    return;
  ComponentGridItemQt* gridItem;
  while (!(gridItem = dynamic_cast<ComponentGridItemQt*>(object)) && (object != this))
    object = object->parentWidget();
  if (!gridItem)
      return;

  QPoint hotSpot = event->pos() - gridItem->pos();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << gridItem->objectName() << QPoint(hotSpot);

  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/x-componentgriditem", itemData);

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(gridItem->grab());
  drag->setHotSpot(hotSpot);

//  child->hide();

  drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction);
//  if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
//    child->close();
//  else
//    child->show();
}
