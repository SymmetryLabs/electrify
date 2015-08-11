#pragma once
#include "globals.h"

#include <cstddef>
#include <functional>
#include <unordered_map>

#include <boost/any.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>

#include "pixel.h"
#include "group.h"
#include "color.h"
#include "signals.h"
#include "socket.h"
#include "frame_context.h"
#include "parameter.h"
#include "engine.h"
#include "data_proxy.h"

static boost::uuids::random_generator nodeUuidGenerator;

/**
 * Nodes are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A node can contain other nodes.
 */
class Node {

protected:
    USING_REACTIVE_DOMAIN(EngineDomain)

public:
    virtual ~Node() {}

    template<typename ConcreteType, typename... Targs>
    static ConcreteType* createNode(Targs&&... Fargs) {
        ConcreteType* node = new ConcreteType(forward<Targs>(Fargs)...);
        node->name <<= ConcreteType::nodeName();
        node->uuid = nodeUuidGenerator();
        return node;
    }

    VarSignalT<string> name = MakeVar<EngineDomain>(string());
    boost::uuids::uuid uuid;

    virtual void init() {}
    virtual void deinit() {}

    /**
     * Tells the node to update its model according to the current time
     */
    virtual void update(const FrameContext&) {}

    // Input

    void registerInput(const string& name, unique_ptr<BaseSocket> inputSocket);
    template <typename V>
    void registerInput(const string& name, SignalX<V>** inputAddr);
    template <typename V>
    void registerInput(const string& name, SignalFunction<V>* inputAddr, const V defaultValue = V());

    BaseSocket* getInput(const string& name) const;

    virtual bool canWireInput(const string& name, const BaseSignal& signal) const;
    virtual void wireInput(const string& name, BaseSignal& signal);

    virtual void registerContextModifier(const string& name,
        ContextModifierChain& contextModifier);

    // Output

    void registerOutput(const string& name, unique_ptr<BaseSignal> signal);
    template <typename V, typename C>
    void registerOutput(const string& name, 
        V (C::* calculate_function_)(const FrameContext& frame) const);

    BaseSignal* getOutput(const string& name) const;

    template <typename V>
    SignalX<V>* getOutput(const string& name) const;

    virtual bool canWireOutputTo(const string& emittingOutputName,
        const Node& receivingNode, const string& receivingInputName) const;
    virtual bool canWireOutputTo(const string& emittingOutputName,
        const BaseSocket& receivingSocket) const;

    virtual void wireOutputTo(const string& emittingOutputName,
        Node& receivingNode, const string& receivingInputName);
    virtual void wireOutputTo(const string& emittingOutputName,
        BaseSocket& receivingSocket);

    // Parameter

    void registerParameter(const string& name, unique_ptr<BaseParameter> parameter);

    template<class Archive>
    void serialize(Archive& archive);

private:
    unordered_map<string, unique_ptr<BaseSocket>> inputs;
    unordered_map<string, unique_ptr<BaseSignal>> outputs;
    unordered_map<string, unique_ptr<BaseParameter>> parameters;

    unordered_map<string, VarSignalT<boost::any>> data;

    template<typename T>
    friend class NodeProxy;

};

template<typename Domain>
class NodeProxy : public DataProxy<EngineDomain, Domain> {

public:
    NodeProxy(shared_ptr<Node> master, ProxyBridge& proxyBridge)
        : DataProxy<EngineDomain, Domain>(master, proxyBridge)
        , name(MakeVar<Domain>(master->name.Value()))
        , uuid(master->uuid)
    {
        this->bindSignal(master->name, this->name);

        inputs.reserve(master->inputs.size());
        for(auto& kv : master->inputs) {
                inputs.push_back(kv.first);
        }

        outputs.reserve(master->outputs.size());
        for(auto& kv : master->outputs) {
                outputs.push_back(kv.first);
        }
    }

    VarSignal<Domain, string> name;
    boost::uuids::uuid uuid;
    vector<string> inputs;
    vector<string> outputs;

    void setName(const string& name_)
    {
        this->template sendCommand([=] (shared_ptr<Node> node) {
            node->name <<= name_;
        });
    }
};

template<typename Domain>
shared_ptr<NodeProxy<Domain>> makeProxy(shared_ptr<Node> object, ProxyBridge& proxyBridge) {
    return make_shared<NodeProxy<Domain>>(object, proxyBridge);
}

#include "node.tpp"
