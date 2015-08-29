#pragma once
#include "globals.h"

#include "node.h"
#include "socket.h"
#include "observable_vector.h"
#include "data_proxy.h"
#include "node_wire.h"
#include "node_socket.h"
#include "node_signal.h"
#include "proxyable.h"

class CompoundNodeProxy;

class CompoundNode : public Node, public Proxyable {

public:
    explicit CompoundNode(const string& name = "Compound Node");
    virtual ~CompoundNode() {}

    virtual void init() override;
    virtual void deinit() override;
    virtual void update(const FrameContext& f) override;

    template <typename Type, typename... Targs>
    Type* makeSubnode(Targs&&... Fargs);
    size_t createSubnode(const string& name);

    size_t addSubnode(unique_ptr<Node> subnode);
    void removeSubnode(Node* subnode);

    Node* getSubnodeByUuid(boost::uuids::uuid uuid);

    // bool canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    //     Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket);
    void unwireSubnode(Node& subnode);
    void removeWire(NodeWire& wire);

    template <typename V>
    void registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());
    template <typename V>
    void registerWirableOutput(const string& name, const V defaultValue = V());

    NodeSocket* getWirableOutput(const string& name);
    void wireOutput(const string& name, NodeSignal& emittingSignal);

    ObservableVector<shared_ptr<Node>> subnodes;
    ObservableVector<shared_ptr<NodeWire>> nodeWires;

private:
    unordered_map<string, NodeSocket*> wirableOutputs;

    SYNTHESIZE_PROXYABLE(CompoundNodeProxy);

};

class CompoundNodeProxy : public NodeProxy {

public:
    CompoundNodeProxy(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge)
    : NodeProxy(master, proxyBridge)
    {}

    void init(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge)
    {
        NodeProxy::init(master, proxyBridge);
        master->subnodes.makeProxySlave(subnodes, proxyBridge);
        master->nodeWires.makeProxySlave(nodeWires, proxyBridge);
    }

    ObservableVector<shared_ptr<NodeProxy>> subnodes;
    ObservableVector<shared_ptr<NodeWireProxy>> nodeWires;

    void addSubnode(const string& name, function<void(size_t)> response)
    {
        this->template sendCommand<CompoundNode, size_t>([=] (shared_ptr<CompoundNode> compoundNode) -> size_t {
            return compoundNode->createSubnode(name);
        }, [=] (size_t pos) {
            response(pos);
        });
    }
    
    void removeSubnode(const NodeProxy& node)
    {
        this->template sendCommand<CompoundNode, Node>(
            [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<Node> node) {
            compoundNode->removeSubnode(node.get());
        }, node);
    }

    void wireSubnodes(const NodeSignalProxy& emittingSignal, const NodeSocketProxy& receivingSocket)
    {
        this->template sendCommand<CompoundNode, NodeSignal, NodeSocket>(
            [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeSignal> emittingSignal, shared_ptr<NodeSocket> receivingSocket) {
            compoundNode->wireSubnodes(*emittingSignal.get(), *receivingSocket.get());
        }, emittingSignal, receivingSocket);
    }
    
    void removeWire(const NodeWireProxy& nodeWire)
    {
        this->template sendCommand<CompoundNode, NodeWire>(
            [] (shared_ptr<CompoundNode> compoundNode, shared_ptr<NodeWire> nodeWire) {
            compoundNode->removeWire(*nodeWire.get());
        }, nodeWire);
    }
};

#include "compound_node.tpp"
