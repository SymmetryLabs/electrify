#include "node_grid.h"

NodeGrid::NodeGrid(CompoundNodeProxy<EngineUiDomain>* compoundNode_)
    : compoundNode(compoundNode_)
{
    {
        addObserver(Observe(compoundNode->subnodes.valueAdded, [this] (const pair<size_t, shared_ptr<NodeProxy<EngineUiDomain>>>& pair) {
            addGridItemWith(pair.first, *pair.second.get());
        }));
        addObserver(Observe(compoundNode->subnodes.valueRemoved, [this] (const pair<size_t, shared_ptr<NodeProxy<EngineUiDomain>>>& pair) {
            removeGridItemWith(pair.first, *pair.second.get());
        }));
        size_t i = 0;
        for (auto& node : compoundNode->subnodes) {
            addGridItemWith(i++, *node);
        }
    }
    {
        addObserver(Observe(compoundNode->nodeWires.valueAdded, [this] (const pair<size_t, reference_wrapper<NodeWire>>& pair) {
            addGridWireWith(pair.first, pair.second);
        }));
        addObserver(Observe(compoundNode->nodeWires.valueRemoved, [this] (const pair<size_t, NodeWire>& pair) {
            removeGridWireWith(pair.first, pair.second);
        }));
        size_t i = 0;
        for (auto& wire : compoundNode->nodeWires) {
            addGridWireWith(i++, wire);
        }
    }
}

void NodeGrid::addNode(string name, float x, float y)
{
    compoundNode->addSubnode(name, [=] (size_t pos) {
        gridItems[pos]->setPos(x, y);
    });
}

void NodeGrid::removeNode()
{
}

NodeGridItem* NodeGrid::nodeWithUuid(boost::uuids::uuid uuid)
{
    for (shared_ptr<NodeGridItem> gridItem : gridItems) {
        if (gridItem->node->uuid == uuid) {
            return gridItem.get();
        }
    }
    return nullptr;
}

NodeGridItem* NodeGrid::addGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node)
{
    vector<shared_ptr<NodeGridItem>>::iterator iter = gridItems.begin() + pos;
    gridItems.insert(iter, make_shared<NodeGridItem>(&node, gridItemCoordinator));
    return gridItems.back().get();
}

shared_ptr<NodeGridItem> NodeGrid::removeGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node)
{
    auto gridItem = move(gridItems[pos]);
    gridItems.erase(gridItems.begin() + pos);
    return gridItem;
}

NodeGridWire* NodeGrid::addGridWireWith(size_t pos, NodeWire& wire)
{
    vector<shared_ptr<NodeGridWire>>::iterator iter = gridWires.begin() + pos;
    NodeGridItem* emittingNode = nodeWithUuid(wire.emittingNodeUuid);
    NodeGridItem* receivingNode = nodeWithUuid(wire.receivingNodeUuid);
    gridWires.insert(iter, make_shared<NodeGridWire>(wire, gridItemCoordinator, *emittingNode, *receivingNode));
    return gridWires.back().get();
}

shared_ptr<NodeGridWire> NodeGrid::removeGridWireWith(size_t pos, NodeWire wire)
{
    auto gridItem = move(gridWires[pos]);
    gridWires.erase(gridWires.begin() + pos);
    return gridItem;
}
