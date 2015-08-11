#include "node.h"

void Node::registerInput(const string& name, unique_ptr<BaseSocket> inputSocket)
{
    inputs[name] = move(inputSocket);
}

BaseSocket* Node::getInput(const string& name) const
{
    try {
        return inputs.at(name).get();
    } catch (out_of_range& e) {
        return nullptr;
    }
}

bool Node::canWireInput(const string& name, const BaseSignal& signal) const
{
    auto input = getInput(name);
    return input && input->acceptsSignal(signal);
}

void Node::wireInput(const string& name, BaseSignal& signal)
{
    getInput(name)->setSignal(&signal);
}

void Node::registerContextModifier(const string& name,
    ContextModifierChain& contextModifier)
{
    getInput(name)->addContextModifier(contextModifier);
}

void Node::registerOutput(const string& name, unique_ptr<BaseSignal> signal)
{
    outputs[name] = move(signal);
}

BaseSignal* Node::getOutput(const string& name) const
{
    try {
        return outputs.at(name).get();
    } catch (out_of_range& e) {
        return nullptr;
    }
}

bool Node::canWireOutputTo(const string& emittingOutputName,
    const Node& receivingNode, const string& receivingInputName) const
{
    auto output = getOutput(emittingOutputName);
    return output && receivingNode.canWireInput(receivingInputName, *output);
}

bool Node::canWireOutputTo(const string& emittingOutputName,
    const BaseSocket& receivingSocket) const
{
    auto output = getOutput(emittingOutputName);
    return output && receivingSocket.acceptsSignal(*output);
}

void Node::wireOutputTo(const string& emittingOutputName,
    Node& receivingNode, const string& receivingInputName)
{
    receivingNode.wireInput(receivingInputName, *getOutput(emittingOutputName));
}

void Node::wireOutputTo(const string& emittingOutputName, BaseSocket& receivingSocket)
{
    receivingSocket.setSignal(getOutput(emittingOutputName));
}

void Node::registerParameter(const string& name, unique_ptr<BaseParameter> parameter)
{
    parameters[name] = move(parameter);
}
