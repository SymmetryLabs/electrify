#pragma once
#include "globals.h"

#include "node.h"

class NodeWire {

public:
  NodeWire(Node& emittingNode, const string& emittingOutputName,
    Node& receivingNode, const string& receivingInputName)
  : emittingNodeUuid(emittingNode.uuid)
  , emittingOutputName(emittingOutputName)
  , receivingNodeUuid(receivingNode.uuid)
  , receivingInputName(receivingInputName)
  {
  }

  boost::uuids::uuid emittingNodeUuid;
  string emittingOutputName;

  boost::uuids::uuid receivingNodeUuid;
  string receivingInputName;

};
