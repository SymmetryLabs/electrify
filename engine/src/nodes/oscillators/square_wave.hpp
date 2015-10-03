template<typename Input>
void SquareWave<Input>::configure(SquareWave<Input>& node, NodeHandle& handle)
{
    Waveform<Input>::configure(node, handle);
    handle.setName("Square wave");
}

template<typename Input>
float SquareWave<Input>::calculate(const FrameContext& frame) const
{
    return this->amplitude(frame) * floor(2 * frame.timeSeconds() * this->frequency(frame) + this->phase(frame));
}
