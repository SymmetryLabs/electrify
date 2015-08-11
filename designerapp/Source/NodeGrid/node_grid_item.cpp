#include "node_grid_item.h"

NodeGridItem::NodeGridItem(NodeProxy<EngineUiDomain>* node, GridItemCoordinator& gridItemCoordinator)
    : node(node)
    , x(MakeVar<EngineUiDomain, float>(0))
    , y(MakeVar<EngineUiDomain, float>(0))
    , selected(MakeVar<EngineUiDomain, bool>(false))
    , gridItemCoordinator(gridItemCoordinator)
{
    // TODO: load persisted x,y for node
}

void NodeGridItem::setPos(float x_, float y_)
{
    x <<= x_;
    y <<= y_;
}

void NodeGridItem::setSelected(bool selected)
{
    gridItemCoordinator.setSelected(*this, selected);
}
