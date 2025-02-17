#include "node_handle.h"

#include <boost/uuid/random_generator.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include "node.h"
#include "node_registrar.h"
#include "node_handle_serializer.h"

CEREAL_REGISTER_TYPE(NodeHandle);

NodeHandle::NodeHandle()
{
    static boost::uuids::random_generator nodeUuidGenerator;
    uuid = nodeUuidGenerator();
}

void NodeHandle::setName(const string& name_)
{
    name <<= name_;
}

string NodeHandle::getName() const
{
    return name.getValue();
}

void NodeHandle::registerInput(const string& name, const shared_ptr<NodeSocket>& inputNodeSocket)
{
    inputs.push_back(inputNodeSocket);
}

void NodeHandle::registerInput(const string& name, const shared_ptr<BaseSocket>& inputSocket)
{
    registerInput(name, make_shared<NodeSocket>(*this, name, inputSocket));
}

NodeSocket* NodeHandle::getInput(const string& name) const
{
    for (const auto& input : inputs) {
        if (input->getName() == name) {
            return input.get();
        }
    }
    return nullptr;
}

const ObservableVector<shared_ptr<NodeSocket>>& NodeHandle::getInputs() const
{
    return inputs;
}

void NodeHandle::registerOutput(const string& name, const shared_ptr<NodeSignal>& outputNodeSignal)
{
    outputs.push_back(outputNodeSignal);
}

void NodeHandle::registerOutput(const string& name, const shared_ptr<BaseSignal>& outputSignal)
{
    registerOutput(name, make_shared<NodeSignal>(*this, name, outputSignal));
}

NodeSignal* NodeHandle::getOutput(const string& name) const
{
    for (const auto& output : outputs) {
        if (output->getName() == name) {
            return output.get();
        }
    }
    return nullptr;
}

const ObservableVector<shared_ptr<NodeSignal>>& NodeHandle::getOutputs() const
{
    return outputs;
}

// void NodeHandle::registerParameter(const string& name, unique_ptr<BaseParameter> parameter)
// {
//     parameters[name] = move(parameter);
// }

const string& NodeHandle::getNodeName() const
{
    return nodeName;
}

void NodeHandle::postCtor()
{
    generateNode();
}

void NodeHandle::postSharedPtrConstruction()
{
    setupNodeDestination();
}

void NodeHandle::generateNode()
{
    NodeRegistrar::getInstance().generateNode(*this);
}

void NodeHandle::setBridge(DataBridge& bridge)
{
    setDataProxies(bridge.getMasterProxy(), bridge.getSlaveProxy());
    node->setDataProxies(bridge.getSlaveProxy(), bridge.getMasterProxy());
}

void NodeHandle::setNode(const shared_ptr<Node>& node_)
{
    node = node_;
    setDestination(node);
}

void NodeHandle::setupNodeDestination()
{
    node->setDestination(shared_from_this());
}
