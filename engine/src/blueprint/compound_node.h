#pragma once
#include "globals.h"

#include "node.h"
#include "socket.h"
#include "observable_vector.h"
#include "data_proxy.h"
#include "node_wire.h"
#include "node_socket.h"
#include "node_signal.h"

class CompoundNodeProxy;

class CompoundNode : public Node {

public:
    explicit CompoundNode(const string& name = "Compound Node");
    virtual ~CompoundNode() = default;

    virtual void init() override;
    virtual void deinit() override;
    virtual void update(const FrameContext& f) override;

    template <typename Type, typename... Targs>
    Type* makeSubnode(Targs&&... Fargs);
    size_t createSubnode(const string& name);

    size_t addSubnode(unique_ptr<Node> subnode);
    void removeSubnode(Node* subnode);

    Node* getSubnodeByUuid(boost::uuids::uuid uuid) const;

    // bool canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    //     Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket);
    void unwireSubnode(Node& subnode);
    void removeWire(NodeWire& wire);

    template <typename V>
    void registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());
    template <typename V>
    void registerWirableOutput(const string& name, const V defaultValue = V());

    NodeSocket* getWirableOutput(const string& name) const;
    void wireOutput(const string& name, NodeSignal& emittingSignal);

    ObservableVector<shared_ptr<Node>> subnodes;
    ObservableVector<shared_ptr<NodeWire>> nodeWires;

private:
    ObservableVector<shared_ptr<NodeSocket>> wirableOutputs;

    SYNTHESIZE_PROXYABLE(CompoundNodeProxy);

};

class CompoundNodeProxy : public NodeProxy {

public:
    CompoundNodeProxy(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge);
    void init(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge);

    ObservableVector<shared_ptr<NodeProxy>> subnodes;
    ObservableVector<shared_ptr<NodeWireProxy>> nodeWires;
    ObservableVector<shared_ptr<NodeSocketProxy>> wirableOutputs;

    void addSubnode(const string& name, function<void(size_t)> response);
    void removeSubnode(const NodeProxy& node);
    void wireSubnodes(const NodeSignalProxy& emittingSignal, const NodeSocketProxy& receivingSocket);
    void removeWire(const NodeWireProxy& nodeWire);
};

#include "compound_node.tpp"
