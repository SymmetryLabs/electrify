#include "component_grid_item.h"
#include "ui_componentgriditem.h"

ComponentGridItem::ComponentGridItem(std::unique_ptr<Component> component_, QWidget *parent) :
    QWidget(parent),
    component(std::move(component_)),
    ui(new Ui::ComponentGridItem)
{
    ui->setupUi(this);
    ui->componentName->setText(QString::fromStdString(component->name));
}

ComponentGridItem::~ComponentGridItem()
{
    delete ui;
}
