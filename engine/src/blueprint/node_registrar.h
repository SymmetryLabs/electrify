#pragma once
#include "globals.h"

#include <unordered_map>

#include "node_handle.h"

class Node;

class NodeRegistrar : public Singleton<NodeRegistrar> {

public:
    template <template <typename> class NodeType, typename HandleType = typename NodeType<FunctionContainer>::handle_t>
    void registerNode(const string& name);

    vector<string> getAvailableNodeNames() const;
    size_t getAvailableNodeCount() const;

    shared_ptr<NodeHandle> getNodeHandle(const string& name) const;
    void generateNode(NodeHandle& handle) const;

private:
    unordered_map<string, function<shared_ptr<NodeHandle>()>> nodeHandleFactories;
    unordered_map<string, function<void(NodeHandle& handle)>> nodeFactories;

};

// Registers a node type
// It can be put in either the header or implementation file
// and can be called multiple times.
//
// Notes: It creates an anonymous namespace so that it can
// define `registered` multiple times.
#define REGISTER_NODE(TYPE)                                             \
    namespace {                                                         \
        template <template <typename> class Type>                       \
        struct NodeRegistration;                                        \
        template <>                                                     \
        struct NodeRegistration<TYPE> {                                 \
            static const bool registered;                               \
            static void unused() { (void)registered; }                  \
        };                                                              \
        const bool NodeRegistration<TYPE>::registered =                 \
                NodeRegistrationEntry<TYPE>::registerEntry(#TYPE);      \
    }

// Helper class to enable static registration of node types
//
// Notes: The registerEntry method only executes once per
// template instantiation of NodeRegistrationEntry,
// regardless of how many times its called.
template <template <typename> class T>
struct NodeRegistrationEntry {
    static bool registerEntry(const std::string& nodeName) {
        static NodeRegistrationEntry<T> instance(nodeName);
        return true;
    }
private:
    explicit NodeRegistrationEntry(const std::string& nodeName) {
        NodeRegistrar::getInstance().registerNode<T>(nodeName);
    }
};

#include "node_registrar.hpp"
