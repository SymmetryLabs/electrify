#include "NodeGridItem.h"

#include "NodeGrid.h"

NodeGridItem::NodeGridItem(NodeProxy<EngineUiDomain>* node, NodeGrid& nodeGrid)
    : node(node)
    , x(MakeVar<EngineUiDomain, float>(0))
    , y(MakeVar<EngineUiDomain, float>(0))
    , selected(MakeVar<EngineUiDomain, bool>(false))
    , nodeGrid(nodeGrid)
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
    nodeGrid.setSelectedNode(*this, selected);
}
