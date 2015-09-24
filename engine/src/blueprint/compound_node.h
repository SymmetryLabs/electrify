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

template<typename Input>
class CompoundNode : public Node {

public:
    explicit CompoundNode(CompoundNodeHandle& nodeHandle);
    virtual ~CompoundNode() = default;

    virtual void init() override;
    virtual void deinit() override;
    virtual void update(const FrameContext& f) override;

    typedef CompoundNodeHandle handle_t;

private:
    ObservableVector<shared_ptr<Node>> subnodes;

};

class CompoundNodeHandle : public NodeHandle {

public:
    virtual ~CompoundNodeHandle() = default;

    template<template<typename> class Type, typename HandleType = typename Type<FunctionContainer>::handle_t, typename... Args>
    HandleType* makeSubnode(Args&&... args);
    size_t createSubnode(const string& name);

    size_t addSubnode(const shared_ptr<NodeHandle>& subnode);
    void removeSubnode(NodeHandle& subnode);

    NodeHandle* getSubnodeByUuid(boost::uuids::uuid uuid) const;

    // bool canWireSubnodes(Node& emittingSubnode, const string& emittingOutputName,
    //     Node& receivingSubnode, const string& receivingInputName);
    void wireSubnodes(NodeSignal& emittingSignal, NodeSocket& receivingSocket);
    void unwireSubnode(NodeHandle& subnode);
    void removeWire(NodeWire& wire);

    template <typename V>
    void registerWirableOutput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());
    template <typename V>
    void registerWirableOutput(const string& name, const V defaultValue = V());

    NodeSocket* getWirableOutput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSocket>>& getWirableOutputs() const;

    void wireOutput(const string& name, NodeSignal& emittingSignal);

    ObservableVector<shared_ptr<NodeHandle>> subnodes;
    ObservableVector<shared_ptr<NodeWire>> nodeWires;

protected:
    shared_ptr<Node> releaseNode(DataBridge& dataBridge) override;

    void setBridge(DataBridge& bridge) override;

private:
    ObservableVector<shared_ptr<NodeSocket>> wirableOutputs;

    DataBridge* dataBridge = nullptr;

    void setSubnodeSlave(ObservableVector<shared_ptr<Node>>& slave);

    template<typename>
    friend class CompoundNode;

};

    // void addSubnode(const string& name, function<void(size_t)> response);
    // void removeSubnode(const NodeProxy& node);
    // void wireSubnodes(const NodeSignalProxy& emittingSignal, const NodeSocketProxy& receivingSocket);
    // void removeWire(const NodeWireProxy& nodeWire);

#include "compound_node.hpp"
