#include "compound_node.h"

void CompoundNode::init()
{
  for (auto& subnode : subnodes) {
    subnode->init();
  }
}

void CompoundNode::deinit()
{
  for (auto& subnode : subnodes) {
    subnode->deinit();
  }
}

void CompoundNode::update(const FrameContext& frame)
{
  for (auto& subnode : subnodes) {
    subnode->update(frame);
  }
}

size_t CompoundNode::createSubnode(const string& name)
{
  NodeRegistrar registrar;
  auto subnode = registrar.getNode(name);
  return addSubnode(move(subnode));
}

size_t CompoundNode::addSubnode(unique_ptr<Node> subnode)
{
  subnodes.push_back(move(subnode));
  return subnodes.size() - 1;
}

void CompoundNode::removeSubnode(Node* subnode)
{
  // TODO: break connections
  removeSharedPtr(subnodes, subnode);
}

bool CompoundNode::canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
  Node& receivingSubnode, const string& receivingInputName)
{
  return emittingSubnode.canWireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
}

void CompoundNode::wireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
  Node& receivingSubnode, const string& receivingInputName)
{
  nodeWires.push_back(NodeWire(emittingSubnode, emittingOutputName, receivingSubnode, receivingInputName));
  return emittingSubnode.wireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
}

void CompoundNode::unwireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
  Node& receivingSubnode, const string& receivingInputName)
{
  // TODO
}

BaseSocket* CompoundNode::getWirableOutput(const string& name)
{
  try {
    return wirableOutputs.at(name);
  } catch (out_of_range& e) {
    return nullptr;
  }
}

void CompoundNode::wireOutput(const string& name,
  Node& emittingSubnode, const string& emittingOutputName)
{
  emittingSubnode.wireOutputTo(emittingOutputName, *getWirableOutput(name));
}
