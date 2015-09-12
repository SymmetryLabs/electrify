#pragma once
#include "globals.h"

#include <unordered_map>

#include "node_handle.h"

class Node;

class NodeRegistrar {

public:
    NodeRegistrar();

    template<typename NodeType, typename HandleType = typename NodeType::handle_t>
    void registerNode(const string& name);

    vector<string> getAvailableNodeNames() const;
    size_t getAvailableNodeCount() const;

    shared_ptr<NodeHandle> getNode(const string& name) const;

private:
    unordered_map<string, function<shared_ptr<NodeHandle>()>> nodeFactories;

};

#include "node_registrar.tpp"
