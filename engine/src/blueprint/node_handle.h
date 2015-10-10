#pragma once
#include "globals.h"

#include <functional>

#include <boost/uuid/uuid.hpp>

#include "signals.h"
#include "socket.h"
#include "node_socket.h"
#include "node_signal.h"
#include "parameter.h"
#include "var.h"
#include "observable_vector.h"
#include "data_transmitter.h"
#include "data_bridge.h"

class Node;
class FunctionContainer;

class NodeHandle : public DataTransmitter {

public:
    NodeHandle();
    virtual ~NodeHandle() = default;

    boost::uuids::uuid uuid;

    void setName(const string& name);
    string getName() const;

    // Input

    void registerInput(const string& name, const shared_ptr<NodeSocket>& inputNodeSocket);
    void registerInput(const string& name, const shared_ptr<BaseSocket>& inputSocket);
    template<typename V>
    void registerInput(const string& name, SignalFunction<V>* inputAddr,
        const V defaultValue = V());

    NodeSocket* getInput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSocket>>& getInputs() const;

    // Output

    void registerOutput(const string& name, const shared_ptr<NodeSignal>& outputNodeSignal);
    void registerOutput(const string& name, const shared_ptr<BaseSignal>& outputSignal);
    template<typename V, typename C>
    void registerOutput(const string& name, 
        V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst);

    NodeSignal* getOutput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSignal>>& getOutputs() const;

    // Parameter

    // void registerParameter(const string& name, unique_ptr<BaseParameter> parameter)

    template<template <typename> class NodeType>
    NodeType<FunctionContainer>& getNode();

    const string& getNodeName() const;

    virtual void postCtor();
    virtual void postSharedPtrConstruction();

    template<typename T>
    shared_ptr<T> getSlave() const;

protected:
    virtual void generateNode();

    virtual void setBridge(DataBridge& bridge);

private:
    
    Var<string> name;

    ObservableVector<shared_ptr<NodeSocket>> inputs;
    ObservableVector<shared_ptr<NodeSignal>> outputs;
    // unordered_map<string, unique_ptr<BaseParameter>> parameters;

    string nodeName;

    shared_ptr<Node> node;
    void setNode(const shared_ptr<Node>& node);
    void setupNodeDestination();

    template<template <typename> class NodeType, typename HandleType>
    friend shared_ptr<HandleType> makeNodeHandle(const string& nodeName);
    template<template <typename> class NodeType, typename HandleType>
    friend void generateNodeForHandle(HandleType& handle);
    friend class CompoundNodeHandle;
    friend class Blueprint;

    template <typename Archive>
    friend void save(Archive& archive, const NodeHandle& handle);
    template <typename Archive>
    friend void load(Archive& archive, NodeHandle& handle);

    ENABLE_TYPE_ERASURE();

};

#define NODE_HANDLE_IMPL()              \
    ENABLE_TYPE_ERASURE();

struct FunctionContainer {
    template<typename ReturnType>
    using type = SignalFunction<ReturnType>;
    typedef FunctionContainer tail;
};

template<template <typename> class NodeType, typename HandleType = typename NodeType<FunctionContainer>::handle_t>
shared_ptr<HandleType> makeNodeHandle(const string& nodeName);

template<template<typename> class NodeType, typename HandleType>
void generateNodeForHandle(HandleType& handle);

#include "node_handle.hpp"
