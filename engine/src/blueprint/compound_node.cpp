#include "compound_node.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include "node_registrar.h"
#include "compound_node_handle_serializer.h"

REGISTER_NODE(CompoundNode);
CEREAL_REGISTER_TYPE(CompoundNodeHandle);

size_t CompoundNodeHandle::createSubnode(const string& name)
{
    return addSubnode(NodeRegistrar::getInstance().getNodeHandle(name));
}

size_t CompoundNodeHandle::addSubnode(const shared_ptr<NodeHandle>& subnode)
{
    subnodes.push_back(subnode);
    return subnodes.size() - 1;
}

void CompoundNodeHandle::removeSubnode(NodeHandle& subnode)
{
    unwireSubnode(subnode);
    removeSharedPtr(subnodes, &subnode);
}

NodeHandle* CompoundNodeHandle::getSubnodeByUuid(boost::uuids::uuid uuid) const
{
    for (const auto& subnode : subnodes) {
        if (subnode->uuid == uuid) {
            return subnode.get();
        }
    }
    return nullptr;
}

// bool CompoundNodeHandle::canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
//     Node& receivingSubnode, const string& receivingInputName)
// {
//     return emittingSubnode.canWireOutputTo(emittingOutputName, receivingSubnode, receivingInputName);
// }

void CompoundNodeHandle::wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket)
{
    nodeWires.push_back(make_shared<NodeWire>(emittingSignal, receivingSocket));
}

void CompoundNodeHandle::unwireSubnode(NodeHandle& subnode)
{
    for (auto iter = nodeWires.begin(); iter != nodeWires.end(); ) {
        const shared_ptr<NodeWire>& wire = *iter;
        if (wire->isAssignedTo(subnode)) {
            wire->disconnect();
            iter = nodeWires.erase(iter);
        } else {
            ++iter;
        }
    }
}

void CompoundNodeHandle::removeWire(NodeWire& nodeWire)
{
    nodeWire.disconnect();
    removeSharedPtr(nodeWires, &nodeWire);
}

void CompoundNodeHandle::registerWirableOutput(const string& name, const shared_ptr<BaseSocket>& socket)
{
    auto nodeSocket = make_shared<NodeSocket>(*this, name, socket);
    wirableOutputs.push_back(nodeSocket);
    registerOutput(name, nodeSocket);
}

NodeSocket* CompoundNodeHandle::getWirableOutput(const string& name) const
{
    for (auto& output : wirableOutputs) {
        if (output->getName() == name) {
            return output.get();
        }
    }
    return nullptr;
}

const ObservableVector<shared_ptr<NodeSocket>>& CompoundNodeHandle::getWirableOutputs() const
{
    return wirableOutputs;
}

void CompoundNodeHandle::wireOutput(const string& name, NodeSignal& emittingSignal)
{
    // emittingSubnode.wireOutputTo(emittingOutputName, *getWirableOutput(name));
}

void CompoundNodeHandle::setBridge(DataBridge& bridge)
{
    NodeHandle::setBridge(bridge);
    dataBridge = &bridge;
    for (const auto& node : subnodes) {
        node->setBridge(bridge);
    }
}

void CompoundNodeHandle::setSubnodeSlave(ObservableVector<shared_ptr<Node>>& slave)
{
    bindObjects(subnodes, slave);
}

// void CompoundNodeProxy::addSubnode(const string& name, function<void(size_t)> response)
// {
//     this->template sendCommand<CompoundNode, size_t>([=] (shared_ptr<CompoundNode> compoundNode) -> size_t {
//         return compoundNode->createSubnode(name);
//     }, [=] (size_t pos) {
//         response(pos);
//     });
// }

// void CompoundNodeProxy::removeSubnode(const NodeProxy& node)
// {
//     this->template sendCommand<CompoundNode, Node>(
//         [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<Node> node) {
//         compoundNode->removeSubnode(node.get());
//     }, node);
// }

// void CompoundNodeProxy::wireSubnodes(const NodeSignalProxy& emittingSignal, const NodeSocketProxy& receivingSocket)
// {
//     this->template sendCommand<CompoundNode, NodeSignal, NodeSocket>(
//         [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeSignal> emittingSignal, shared_ptr<NodeSocket> receivingSocket) {
//         compoundNode->wireSubnodes(*emittingSignal.get(), *receivingSocket.get());
//     }, emittingSignal, receivingSocket);
// }

// void CompoundNodeProxy::removeWire(const NodeWireProxy& nodeWire)
// {
//     this->template sendCommand<CompoundNode, NodeWire>(
//         [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeWire> nodeWire) {
//         compoundNode->removeWire(*nodeWire.get());
//     }, nodeWire);
// }
