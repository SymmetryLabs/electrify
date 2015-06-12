#include "component.h"

void Component::registerOutput(const string& name, unique_ptr<BaseSignal> signal) {
  outputs[name] = move(signal);
}

void Component::registerInput(const string& name, unique_ptr<BaseSocket> input) {
  inputs[name] = move(input);
}
