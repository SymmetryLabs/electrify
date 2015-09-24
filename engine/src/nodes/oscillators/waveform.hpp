template<typename Input>
Waveform<Input>::Waveform(NodeHandle& nodeHandle)
: BasicNode<Input, float>(nodeHandle)
{
    nodeHandle.registerInput("amplitude", &amplitude, 1.0f);
    nodeHandle.registerInput("frequency", &frequency, 1.0f);
    nodeHandle.registerInput("phase", &phase);
}
