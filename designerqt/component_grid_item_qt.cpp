#include "component_grid_item_qt.h"
#include "ui_component_grid_item_qt.h"

#include <QDebug>

ComponentGridItemQt::ComponentGridItemQt(ComponentGridItem* componentGridItem_, QWidget *parent) :
  QWidget(parent),
  componentGridItem(componentGridItem_),
  ui(new Ui::ComponentGridItemQt)
{
  ui->setupUi(this);

  setObjectName(QString::fromStdString(componentGridItem->component->uuid));

  observeWithStart(componentGridItem->component->name, [&] (string name) {
    ui->componentName->setText(QString::fromStdString(name));
  });

  qDebug() << "Added" << QString::fromStdString(componentGridItem->component->name.Value());

  observeWithStart(componentGridItem->x, [this] (float) {
    move(componentGridItem->x.Value(), componentGridItem->y.Value());
  });
  observeWithStart(componentGridItem->y, [this] (float) {
    move(componentGridItem->x.Value(), componentGridItem->y.Value());
  });
}

ComponentGridItemQt::~ComponentGridItemQt()
{
  delete ui;
}

void ComponentGridItemQt::setPos(QPoint pos)
{
  componentGridItem->setPos(pos.x(), pos.y());
}
