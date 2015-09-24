template<typename Input>
SawWave<Input>::SawWave(NodeHandle& nodeHandle)
: Waveform<Input>(nodeHandle)
{
    nodeHandle.setName("Sawtooth wave");
}

template<typename Input>
float SawWave<Input>::calculate(const FrameContext& frame) const
{
    float unused;
    return this->amplitude(frame) * modf(frame.timeSeconds() * this->frequency(frame) + this->phase(frame), &unused);
}
