template<typename Input>
SinWave<Input>::SinWave(NodeHandle& nodeHandle)
: Waveform<Input>(nodeHandle)
{
    nodeHandle.setName("Sin wave");
}

template<typename Input>
float SinWave<Input>::calculate(const FrameContext& frame) const
{
    return this->amplitude(frame) * (sin(M_2_PI * frame.timeSeconds() * this->frequency(frame) + this->phase(frame)) + 1) / 2;
}
