#ifndef COMPONENTGRID_H
#define COMPONENTGRID_H

#include <QWidget>
#include <QDragEnterEvent>

#include "component_registrar.h"

namespace Ui {
class ComponentGrid;
}

class ComponentGrid : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentGrid(QWidget *parent = 0);
    ~ComponentGrid();

private:
    Ui::ComponentGrid *ui;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    ComponentRegistrar componentRegistrar;
};

#endif // COMPONENTGRID_H
