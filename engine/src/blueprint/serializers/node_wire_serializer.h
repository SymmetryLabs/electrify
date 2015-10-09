#pragma once
#include "globals.h"

class NodeWire;

template <typename Archive>
void save(Archive& archive, const NodeWire& nodeWire)
{
    archive(
        cereal::make_nvp("sourceHandle", nodeWire.sourceHandle),
        cereal::make_nvp("sourceName", nodeWire.sourceName),
        cereal::make_nvp("destinationHandle", nodeWire.destinationHandle),
        cereal::make_nvp("destinationName", nodeWire.destinationName)
    );
}

template <typename Archive>
void load(Archive& archive, NodeWire& nodeWire)
{
    archive(
        cereal::make_nvp("sourceHandle", nodeWire.sourceHandle),
        cereal::make_nvp("sourceName", nodeWire.sourceName),
        cereal::make_nvp("destinationHandle", nodeWire.destinationHandle),
        cereal::make_nvp("destinationName", nodeWire.destinationName)
    );
    nodeWire.populateSignals();
    nodeWire.connect();
}
