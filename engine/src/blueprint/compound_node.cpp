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

Node* CompoundNode::getSubnodeByUuid(boost::uuids::uuid uuid) const
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
    for (auto iter = nodeWires.begin(); iter != nodeWires.end(); ) {
        const shared_ptr<NodeWire>& wire = *iter;
        if (&wire->source.node == &subnode
                || &wire->destination.node == &subnode) {
            wire->disconnect();
            iter = nodeWires.erase(iter);
        } else {
            ++iter;
        }
    }
}

void CompoundNode::removeWire(NodeWire& nodeWire)
{
    nodeWire.disconnect();
    removeSharedPtr(nodeWires, &nodeWire);
}

NodeSocket* CompoundNode::getWirableOutput(const string& name) const
{
    for (auto& output : wirableOutputs) {
        if (output->getName() == name) {
            return output.get();
        }
    }
    return nullptr;
}

void CompoundNode::wireOutput(const string& name, NodeSignal& emittingSignal)
{
    // emittingSubnode.wireOutputTo(emittingOutputName, *getWirableOutput(name));
}

CompoundNodeProxy::CompoundNodeProxy(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge)
: NodeProxy(master, proxyBridge)
{
    master->subnodes.makeProxySlave(subnodes, proxyBridge);
    master->wirableOutputs.makeProxySlave(wirableOutputs, proxyBridge);
    master->nodeWires.makeProxySlave(nodeWires, proxyBridge);
}

void CompoundNodeProxy::addSubnode(const string& name, function<void(size_t)> response)
{
    this->template sendCommand<CompoundNode, size_t>([=] (shared_ptr<CompoundNode> compoundNode) -> size_t {
        return compoundNode->createSubnode(name);
    }, [=] (size_t pos) {
        response(pos);
    });
}

void CompoundNodeProxy::removeSubnode(const NodeProxy& node)
{
    this->template sendCommand<CompoundNode, Node>(
        [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<Node> node) {
        compoundNode->removeSubnode(node.get());
    }, node);
}

void CompoundNodeProxy::wireSubnodes(const NodeSignalProxy& emittingSignal, const NodeSocketProxy& receivingSocket)
{
    this->template sendCommand<CompoundNode, NodeSignal, NodeSocket>(
        [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeSignal> emittingSignal, shared_ptr<NodeSocket> receivingSocket) {
        compoundNode->wireSubnodes(*emittingSignal.get(), *receivingSocket.get());
    }, emittingSignal, receivingSocket);
}

void CompoundNodeProxy::removeWire(const NodeWireProxy& nodeWire)
{
    this->template sendCommand<CompoundNode, NodeWire>(
        [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeWire> nodeWire) {
        compoundNode->removeWire(*nodeWire.get());
    }, nodeWire);
}
