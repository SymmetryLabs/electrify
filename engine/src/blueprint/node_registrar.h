#pragma once
#include "globals.h"

#include <unordered_map>

#include "node_handle.h"

class Node;

class NodeRegistrar {

public:
    NodeRegistrar();

    template<template<typename> class NodeType, typename HandleType = typename NodeType<FunctionContainer>::handle_t>
    void registerNode(const string& name);

    vector<string> getAvailableNodeNames() const;
    size_t getAvailableNodeCount() const;

    shared_ptr<NodeHandle> getNodeHandle(const string& name) const;
    void generateNode(NodeHandle& handle) const;

private:
    unordered_map<string, function<shared_ptr<NodeHandle>()>> nodeHandleFactories;
    unordered_map<string, function<void(NodeHandle& handle)>> nodeFactories;

};

#include "node_registrar.hpp"
