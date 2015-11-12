template <typename Input>
void SawWave<Input>::configure(SawWave<Input>& node, NodeHandle& handle)
{
    Waveform<Input>::configure(node, handle);
    handle.setName("Sawtooth wave");
}

template <typename Input>
float SawWave<Input>::calculate(const FrameContext& frame) const
{
    float unused;
    return this->amplitude(frame) * modf(frame.timeSeconds() * this->frequency(frame) + this->phase(frame), &unused);
}
