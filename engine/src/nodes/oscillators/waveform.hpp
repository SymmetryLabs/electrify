template<typename Input>
void Waveform<Input>::configure(Waveform<Input>& node, NodeHandle& handle)
{
    BasicNode<Skip<Input, 3>, float>::configure(node, handle);
    handle.registerInput("amplitude", node.generateInput(&node.amplitude, 1.0f));
    handle.registerInput("frequency", node.generateInput(&node.frequency, 1.0f));
    handle.registerInput("phase", node.generateInput(&node.phase));
}
