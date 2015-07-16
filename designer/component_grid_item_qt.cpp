#include "component_grid_item_qt.h"
#include "ui_component_grid_item_qt.h"

ComponentGridItemQt::ComponentGridItemQt(std::unique_ptr<Component> component_, QWidget *parent) :
  QWidget(parent),
  component(std::move(component_)),
  ui(new Ui::ComponentGridItemQt)
{
  ui->setupUi(this);
  ui->componentName->setText(QString::fromStdString(component->name));
}

ComponentGridItemQt::~ComponentGridItemQt()
{
  delete ui;
}
