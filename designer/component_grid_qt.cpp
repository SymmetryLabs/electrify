#include "component_grid_qt.h"
#include "ui_componentgrid.h"

#include <QtDebug>
#include <QMimeData>

#include "component_grid_item_qt.h"

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

        auto gridItem = new ComponentGridItemQt(componentRegistrar.getComponent(name), this);
        gridItem->move(event->pos());
        gridItem->show();
    }

    event->acceptProposedAction();
}
