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
    template <typename V>
    void registerInput(const string& name, SignalFunction<V>* inputAddr,
        const V defaultValue = V());

    NodeSocket* getInput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSocket>>& getInputs() const;

    // Output

    void registerOutput(const string& name, const shared_ptr<NodeSignal>& outputNodeSignal);
    void registerOutput(const string& name, const shared_ptr<BaseSignal>& outputSignal);
    template <typename V, typename C>
    void registerOutput(const string& name, 
        V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst);

    NodeSignal* getOutput(const string& name) const;
    const ObservableVector<shared_ptr<NodeSignal>>& getOutputs() const;

    // Parameter

    // void registerParameter(const string& name, unique_ptr<BaseParameter> parameter)

    // template<typename Archive>
    // void serialize(Archive& archive);

    template<typename NodeType>
    NodeType& getNode();

protected:
    virtual shared_ptr<Node> releaseNode(DataBridge& dataBridge);

    virtual void setBridge(DataBridge& bridge);

private:
    
    Var<string> name;

    ObservableVector<shared_ptr<NodeSocket>> inputs;
    ObservableVector<shared_ptr<NodeSignal>> outputs;
    // unordered_map<string, unique_ptr<BaseParameter>> parameters;

    shared_ptr<Node> node;
    void setNode(const shared_ptr<Node>& node);

    template<typename NodeType, typename HandleType, typename... Args>
    friend shared_ptr<HandleType> makeNodeHandle(Args&&... args);
    friend class CompoundNodeHandle;

};

template<typename NodeType, typename HandleType = typename NodeType::handle_t, typename... Args>
shared_ptr<HandleType> makeNodeHandle(Args&&... args);

#include "node_handle.hpp"
