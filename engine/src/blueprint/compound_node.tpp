#include "node_registrar.h"

template <typename Type, typename... Targs>
Type* CompoundNode::makeSubnode(Targs&&... Fargs)
{
  auto subnode = unique_ptr<Type>(Node::createNode<Type>(forward<Targs>(Fargs)...));
  auto subnodePtr = subnode.get();
  addSubnode(move(subnode));
  return subnodePtr;
}

template <typename V>
Socket<V>* CompoundNode::registerWirableOutput(const string& name)
{
  Socket<V>* output = new Socket<V>();
  registerOutput(name, unique_ptr<BaseSignal> {output});
  wirableOutputs[name] = output;
  return output;
}
