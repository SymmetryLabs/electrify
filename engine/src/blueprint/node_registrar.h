#pragma once
#include "globals.h"

#include "node.h"

class NodeRegistrar {

public:
  NodeRegistrar();

  template<typename ClassType>
  void registerNode();

  vector<string> getAvailableNodeNames() const;
  size_t getAvailableNodeCount() const;

  template<typename ClassType = Node>
  unique_ptr<ClassType> getNode(const string& name) const;

private:
  unordered_map<string, function<Node* ()>> nodeFactories;

};

#include "node_registrar.tpp"
