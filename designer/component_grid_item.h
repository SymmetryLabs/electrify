#ifndef COMPONENTGRIDITEM_H
#define COMPONENTGRIDITEM_H

#include <QWidget>

#include "component.h"

namespace Ui {
class ComponentGridItem;
}

class ComponentGridItem : public QWidget
{
    Q_OBJECT

public:
    ComponentGridItem(std::unique_ptr<Component> component, QWidget *parent = 0);
    ~ComponentGridItem();

private:
    Ui::ComponentGridItem *ui;

    std::unique_ptr<Component> component;
};

#endif // COMPONENTGRIDITEM_H
