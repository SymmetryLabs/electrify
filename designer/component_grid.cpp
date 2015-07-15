#include "component_grid.h"
#include "ui_componentgrid.h"

#include <QtDebug>
#include <QMimeData>

#include "component_grid_item.h"

ComponentGrid::ComponentGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentGrid)
{
    ui->setupUi(this);
}

ComponentGrid::~ComponentGrid()
{
    delete ui;
}

void ComponentGrid::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        event->acceptProposedAction();
    }
}

void ComponentGrid::dropEvent(QDropEvent *event)
{
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        int row, col;
        QMap<int,  QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        std::string name = roleDataMap[0].toString().toStdString();

        auto gridItem = new ComponentGridItem(componentRegistrar.getComponent(name), this);
        gridItem->move(event->pos());
        gridItem->show();
    }

    event->acceptProposedAction();
}
