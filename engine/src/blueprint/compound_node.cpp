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

Node* CompoundNode::getSubnodeByUuid(boost::uuids::uuid uuid)
{
    for (const auto& subnode : subnodes) {
        if (subnode->uuid == uuid) {
            return subnode.get();
        }
    }
    return nullptr;
}

bool CompoundNode::canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    Node& receivingSubnode, const string& receivingInputName)
{
    return emittingSubnode.canWireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
}

void CompoundNode::wireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    Node& receivingSubnode, const string& receivingInputName)
{
    NodeSocket emittingSocket(emittingSubnode.uuid, emittingOutputName);
    NodeSocket receivingSocket(receivingSubnode.uuid, receivingInputName);
    nodeWires.push_back(NodeWire(emittingSocket, receivingSocket));
    return emittingSubnode.wireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
}
void CompoundNode::wireSubnodes(const NodeSocket& emittingSocket, const NodeSocket& receivingSocket)
{
    Node* emittingSubnode = getSubnodeByUuid(emittingSocket.nodeUuid);
    Node* receivingSubnode = getSubnodeByUuid(receivingSocket.nodeUuid);
    wireSubnodes(*emittingSubnode, emittingSocket.socketName, *receivingSubnode, receivingSocket.socketName);
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
