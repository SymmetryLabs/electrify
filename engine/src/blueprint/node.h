#pragma once
#include "globals.h"

#include "frame_context.h"
#include "data_transmitter.h"
#include "node_handle.h"

/**
 * Nodes are the building blocks of the Symmetry Engine. They receive inputs, and provide 
 * outputs.
 * A node can contain other nodes.
 */
class Node : public DataTransmitter {

public:
    explicit Node(NodeHandle& nodeHandle);
    virtual ~Node() = default;

    virtual void init() {}
    virtual void deinit() {}

    /**
     * Tells the node to update its model according to the current time
     */
    virtual void update(const FrameContext&) {}

    typedef NodeHandle handle_t;

};
