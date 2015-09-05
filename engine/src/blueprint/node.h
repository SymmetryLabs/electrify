#pragma once
#include "globals.h"

#include <cstddef>
#include <functional>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signals.h"
#include "socket.h"
#include "frame_context.h"
#include "parameter.h"
#include "engine.h"
#include "data_proxy.h"
#include "node_socket.h"
#include "node_signal.h"
#include "proxyable.h"
#include "var.h"
#include "observable_vector.h"

class NodeProxy;

/**
 * Nodes are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A node can contain other nodes.
 */
class Node : public Proxyable {

public:
    explicit Node(const string& name);
    virtual ~Node() = default;

    template<typename ConcreteType, typename... Targs>
    static ConcreteType* createNode(Targs&&... Fargs) {
        ConcreteType* node = new ConcreteType(forward<Targs>(Fargs)...);
        return node;
    }

    Var<string> name;
    boost::uuids::uuid uuid;

    virtual void init() {}
    virtual void deinit() {}

    /**
     * Tells the node to update its model according to the current time
     */
    virtual void update(const FrameContext&) {}

    // Input

    void registerInput(const string& name, const shared_ptr<NodeSocket>& inputNodeSocket);
    void registerInput(const string& name, unique_ptr<BaseSocket>&& inputSocket);
    template <typename V>
    void registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());

    virtual NodeSocket* getInput(const string& name) const;

    // Output

    void registerOutput(const string& name, const shared_ptr<NodeSignal>& outputNodeSignal);
    void registerOutput(const string& name, unique_ptr<BaseSignal>&& signal);
    template <typename V, typename C>
    void registerOutput(const string& name, 
        V (C::* calculate_function_)(const FrameContext& frame) const);

    virtual NodeSignal* getOutput(const string& name) const;

    // Parameter

    // void registerParameter(const string& name, unique_ptr<BaseParameter> parameter);

    // template<class Archive>
    // void serialize(Archive& archive);

private:

    ObservableVector<shared_ptr<NodeSocket>> inputs;
    ObservableVector<shared_ptr<NodeSignal>> outputs;
    // unordered_map<string, unique_ptr<BaseParameter>> parameters;

    // unordered_map<string, Var<boost::any>> data;

    SYNTHESIZE_PROXYABLE(NodeProxy);

};

class NodeProxy : public DataProxy {

public:
    NodeProxy(shared_ptr<Node> master, ProxyBridge& proxyBridge);
    void init(shared_ptr<Node> master, ProxyBridge& proxyBridge);

    Var<string> name;
    boost::uuids::uuid uuid;
    ObservableVector<shared_ptr<NodeSocketProxy>> inputs;
    ObservableVector<shared_ptr<NodeSignalProxy>> outputs;

    void setName(const string& name);
};

#include "node.tpp"
