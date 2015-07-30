#include "component_grid_item_qt.h"
#include "ui_component_grid_item_qt.h"

#include <QDebug>

ComponentGridItemQt::ComponentGridItemQt(ComponentGridItem* componentGridItem_, QWidget *parent) :
  QWidget(parent),
  componentGridItem(componentGridItem_),
  ui(new Ui::ComponentGridItemQt)
{
  ui->setupUi(this);
//  Observe<EngineUiDomain>(componentGridItem->component->name, [&] (string name) {
//    ui->componentName->setText(QString::fromStdString(name));
//  });
  ui->componentName->setText(QString::fromStdString(componentGridItem->component->name.Value()));

  qDebug() << QString::fromStdString(componentGridItem->component->name.Value());

  addObserver(Observe<EngineUiDomain>(componentGridItem->x, [this] (float) {
    move(componentGridItem->x.Value(), componentGridItem->y.Value());
  }));
  addObserver(Observe<EngineUiDomain>(componentGridItem->y, [this] (float) {
    move(componentGridItem->x.Value(), componentGridItem->y.Value());
  }));

  move(componentGridItem->x.Value(), componentGridItem->y.Value());
}

ComponentGridItemQt::~ComponentGridItemQt()
{
  delete ui;
}
