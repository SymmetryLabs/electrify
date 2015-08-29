#include "compound_node.h"

CompoundNode::CompoundNode(const string& name)
: Node(name)
{
}

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
    unwireSubnode(*subnode);
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

// bool CompoundNode::canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
//     Node& receivingSubnode, const string& receivingInputName)
// {
//     return emittingSubnode.canWireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
// }

void CompoundNode::wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket)
{
    nodeWires.push_back(make_shared<NodeWire>(emittingSignal, receivingSocket));
}

void CompoundNode::unwireSubnode(Node& subnode)
{
//     for (auto iter = nodeWires.begin(); iter != nodeWires.end(); ) {
//         NodeWire& wire = *iter;
//         if (wire.emittingSocket.nodeUuid == subnode.uuid
//                 || wire.receivingSocket.nodeUuid == subnode.uuid) {
//             wire.unwireOutputTo()
//             iter = nodeWires.erase(iter);
//         } else {
//             ++iter;
//         }
//     }
}

void CompoundNode::removeWire(NodeWire& nodeWire)
{
    // unwireSubnode(*subnode);
    // removeSharedPtr(subnodes, subnode);
}

NodeSocket* CompoundNode::getWirableOutput(const string& name)
{
    try {
        return wirableOutputs.at(name);
    } catch (out_of_range& e) {
        return nullptr;
    }
}

void CompoundNode::wireOutput(const string& name, NodeSignal& emittingSignal)
{
    // emittingSubnode.wireOutputTo(emittingOutputName, *getWirableOutput(name));
}

SYNTHESIZE_PROXYABLE_IMPL(CompoundNode, CompoundNodeProxy);
