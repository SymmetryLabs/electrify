#include "node_grid.h"

NodeGrid::NodeGrid(CompoundNodeProxy<EngineUiDomain>* compoundNode_)
  : compoundNode(compoundNode_)
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

void NodeGrid::addNode(string name, float x, float y)
{
  compoundNode->addSubnode(name, [=] (size_t pos) {
    gridItems[pos]->setPos(x, y);
  });
}

void NodeGrid::removeNode()
{
}

NodeGridItem* NodeGrid::addGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node)
{
  vector<shared_ptr<NodeGridItem>>::iterator iter = gridItems.begin() + pos;
  gridItems.insert(iter, make_shared<NodeGridItem>(&node));
  return gridItems.back().get();
}

shared_ptr<NodeGridItem> NodeGrid::removeGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node)
{
  auto gridItem = move(gridItems[pos]);
  gridItems.erase(gridItems.begin() + pos);
  return gridItem;
}
