#pragma once
#include "globals.h"

#include <boost/uuid/uuid.hpp>

// enum class NodeSocketDirection { INPUT, OUTPUT };

class NodeSocket {

public:
    NodeSocket() {}
    NodeSocket(boost::uuids::uuid nodeUuid, string socketName);
 
    boost::uuids::uuid nodeUuid;
    string socketName;

    // NodeSocketDirection direction;

};
