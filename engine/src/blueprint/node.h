#pragma once
#include "globals.h"

#include "frame_context.h"
#include "data_transmitter.h"
#include "node_handle.h"
#include "node_registrar.h"
#include "enable_type_erasure.h"

/**
 * Nodes are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A node can contain other nodes.
 */
class Node : public DataTransmitter {

public:
    virtual ~Node() = default;

    static void configure(Node& node, NodeHandle& nodeHandle);

    virtual void init() {}
    virtual void deinit() {}

    /**
     * Tells the node to update its model according to the current time
     */
    virtual void update(const FrameContext&) {}

    typedef NodeHandle handle_t;

private:
    ENABLE_TYPE_ERASURE();

};

#define NODE_IMPL()                     \
        ENABLE_TYPE_ERASURE();

#define NODE_IMPL_ABSTRACT()            \
        ENABLE_TYPE_ERASURE_ABSTRACT();

template<typename In, int N, typename Type>
using Def = typename GetNum<In, N>::type::template type<Type>;

template<typename In, int N>
using Skip = typename GetNum<In, N>::type;
