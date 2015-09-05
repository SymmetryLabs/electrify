#include "node.h"

#include <boost/uuid/random_generator.hpp>

Node::Node(const string& name)
: name(Var<string>(name))
{
    static boost::uuids::random_generator nodeUuidGenerator;
    uuid = nodeUuidGenerator();
}

void Node::registerInput(const string& name, const shared_ptr<NodeSocket>& inputNodeSocket)
{
    inputs.push_back(inputNodeSocket);
}

void Node::registerInput(const string& name, unique_ptr<BaseSocket>&& inputSocket)
{
    inputs.push_back(make_shared<NodeSocket>(*this, name, move(inputSocket)));
}

NodeSocket* Node::getInput(const string& name) const
{
    for (const auto& input : inputs) {
        if (input->getName() == name) {
            return input.get();
        }
    }
    return nullptr;
}

void Node::registerOutput(const string& name, const shared_ptr<NodeSignal>& outputNodeSignal)
{
    outputs.push_back(outputNodeSignal);
}

void Node::registerOutput(const string& name, unique_ptr<BaseSignal>&& signal)
{
    outputs.push_back(make_shared<NodeSignal>(*this, name, move(signal)));
}

NodeSignal* Node::getOutput(const string& name) const
{
    for (const auto& output : outputs) {
        if (output->getName() == name) {
            return output.get();
        }
    }
    return nullptr;
}

// void Node::registerParameter(const string& name, unique_ptr<BaseParameter> parameter)
// {
//     parameters[name] = move(parameter);
// }

NodeProxy::NodeProxy(shared_ptr<Node> master, ProxyBridge& proxyBridge)
: DataProxy(master, proxyBridge)
, name(Var<string>(master->name.getValue()))
, uuid(master->uuid)
{
    this->bind(master->name, this->name);

    master->inputs.makeProxySlave(inputs, proxyBridge);
    master->outputs.makeProxySlave(outputs, proxyBridge);
}

void NodeProxy::setName(const string& name_)
{
    sendCommand<Node>([=] (shared_ptr<Node> node) {
        node->name << name_;
    });
}
