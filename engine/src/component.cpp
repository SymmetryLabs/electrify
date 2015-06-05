#include "component.h"

Component::Component()
{

};

Component::~Component()
{
  
};

void Component::update(double time)
{

};

void Component::notify(/*TODO PASSING FORMAT*/)
{

};

void Component::addOutput(std::string output_name, BaseSignal *output_signal)
{
	outputs[output_name] = output_signal;
}
void Component::addInput(std::string input_name, BaseSignal *input_signal)
{
	inputs[input_name] = input_signal;
}