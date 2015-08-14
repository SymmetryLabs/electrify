#pragma once
#include "globals.h"

#include "node.h"
#include "socket.h"
#include "observable_vector.h"
#include "data_proxy.h"
#include "node_wire.h"
#include "node_socket.h"

class CompoundNode : public Node {

public:
    static const string nodeName() { return "Compound Node"; }

    virtual void init() override;
    virtual void deinit() override;
    virtual void update(const FrameContext& f) override;

    template <typename Type, typename... Targs>
    Type* makeSubnode(Targs&&... Fargs);
    size_t createSubnode(const string& name);

    size_t addSubnode(unique_ptr<Node> subnode);
    void removeSubnode(Node* subnode);

    Node* getSubnodeByUuid(boost::uuids::uuid uuid);

    bool canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
        Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
        Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(const NodeSocket& emittingSocket, const NodeSocket& receivingSocket);
    void unwireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
        Node& receivingSubnode, const string& receivingInputName);

    template <typename V>
    Socket<V>* registerWirableOutput(const string& name);

    BaseSocket* getWirableOutput(const string& name);
    void wireOutput(const string& name,
        Node& emittingSubnode, const string& emittingOutputName);

    ObservableVector<EngineDomain, shared_ptr<Node>> subnodes;
    ObservableVector<EngineDomain, NodeWire> nodeWires;

private:
    unordered_map<string, BaseSocket*> wirableOutputs;

    template<typename T>
    friend class CompoundNodeProxy;

};

template<typename Domain>
class CompoundNodeProxy : public NodeProxy<Domain> {

public:
    CompoundNodeProxy(shared_ptr<CompoundNode> master, ProxyBridge& proxyBridge)
        : NodeProxy<Domain>(master, proxyBridge)
    {
        master->subnodes.makeProxySlave<Domain, NodeProxy<Domain>>(subnodes, proxyBridge);
        master->nodeWires.makeProxySlave<Domain>(nodeWires, proxyBridge);
    }

    ObservableVector<Domain, shared_ptr<NodeProxy<Domain>>, EngineDomain> subnodes;
    ObservableVector<Domain, NodeWire, EngineDomain> nodeWires;

    void addSubnode(const string& name, function<void(size_t)> response)
    {
        this->template sendCommand<CompoundNode, size_t>([=] (shared_ptr<CompoundNode> compoundNode) -> size_t {
            return compoundNode->createSubnode(name);
        }, [=] (size_t pos) {
            response(pos);
        });
    }

    void wireSubnodes(const NodeSocket& emittingSocket, const NodeSocket& receivingSocket)
    {
        this->template sendCommand<CompoundNode>([=] (shared_ptr<CompoundNode> compoundNode) {
            return compoundNode->wireSubnodes(emittingSocket, receivingSocket);
        });
    }
};

template<typename Domain>
shared_ptr<CompoundNodeProxy<Domain>> makeProxy(shared_ptr<CompoundNode> object, ProxyBridge& proxyBridge) {
    return make_shared<CompoundNodeProxy<Domain>>(object, proxyBridge);
}

#include "compound_node.tpp"
