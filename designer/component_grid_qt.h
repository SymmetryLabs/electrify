#ifndef COMPONENTGRIDQT_H
#define COMPONENTGRIDQT_H

#include <QWidget>
#include <QDragEnterEvent>

#include "component_registrar.h"

namespace Ui {
class ComponentGridQt;
}

class ComponentGridQt : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentGridQt(QWidget *parent = 0);
    ~ComponentGridQt();

private:
    Ui::ComponentGridQt* ui;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    ComponentRegistrar componentRegistrar;
};

#endif // COMPONENTGRIDQT_H
