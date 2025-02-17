#pragma once
#include "globals.h"

#include "node.h"
#include "node_handle.h"
#include "socket.h"
#include "observable_vector.h"
#include "node_wire.h"
#include "node_socket.h"
#include "node_signal.h"

class CompoundNodeHandle;

template <typename Input>
class CompoundNode : public Node {

public:
    virtual ~CompoundNode() = default;

    static void configure(CompoundNode<Input>& node, CompoundNodeHandle& handle);

    virtual void init() override;
    virtual void deinit() override;
    virtual void update(const FrameContext& f) override;

    typedef CompoundNodeHandle handle_t;

    size_t getNumSubnodes() const;

    template <typename V>
    shared_ptr<BaseSocket> generateWirableOutput(SignalFunction<V>* inputAddr, const V defaultValue = V());
    template <typename V>
    shared_ptr<BaseSocket> generateWirableOutput(const V defaultValue = V());

private:
    ObservableVector<shared_ptr<Node>> subnodes;

    vector<shared_ptr<BaseSocket>> wirableOutputs;

    NODE_IMPL();

};

class CompoundNodeHandle : public NodeHandle {

public:
    virtual ~CompoundNodeHandle() = default;

    template <template <typename> class Type, typename HandleType = typename Type<FunctionContainer>::handle_t>
    HandleType* makeSubnode(const string& name);
    size_t createSubnode(const string& name);

    size_t addSubnode(const shared_ptr<NodeHandle>& subnode);
    void removeSubnode(NodeHandle& subnode);

    NodeHandle* getSubnodeByUuid(boost::uuids::uuid uuid) const;

    // bool canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    //     Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket);
    void unwireSubnode(NodeHandle& subnode);
    void removeWire(NodeWire& wire);

    void registerWirableOutput(const string& name, const shared_ptr<BaseSocket>& socket);

    NodeSocket* getWirableOutput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSocket>>& getWirableOutputs() const;

    void wireOutput(const string& name, NodeSignal& emittingSignal);

    ObservableVector<shared_ptr<NodeHandle>> subnodes;
    ObservableVector<shared_ptr<NodeWire>> nodeWires;

protected:
    void setBridge(DataBridge& bridge) override;

private:
    ObservableVector<shared_ptr<NodeSocket>> wirableOutputs;

    DataBridge* dataBridge = nullptr;

    void setSubnodeSlave(ObservableVector<shared_ptr<Node>>& slave);

    template <typename>
    friend class CompoundNode;

    template <typename Archive>
    friend void serialize(Archive& archive, CompoundNodeHandle& handle);

    NODE_HANDLE_IMPL();

};

#include "compound_node.hpp"
