#include "node_registrar.h"

#include "node.h"
#include "node_handle.h"

#include "nodes.h"

vector<string> NodeRegistrar::getAvailableNodeNames() const
{
    vector<string> keys;
    keys.reserve(nodeHandleFactories.size());
    for(auto kv : nodeHandleFactories) {
        keys.push_back(kv.first);
    }
    return keys;
}

size_t NodeRegistrar::getAvailableNodeCount() const
{
    return nodeHandleFactories.size();
}

shared_ptr<NodeHandle> NodeRegistrar::getNodeHandle(const string& name) const
{
    return nodeHandleFactories.at(name)();
}

void NodeRegistrar::generateNode(NodeHandle& handle) const
{
    nodeFactories.at(handle.getNodeName())(handle);
}
