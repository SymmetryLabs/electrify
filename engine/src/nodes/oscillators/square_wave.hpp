template<typename Input>
SquareWave<Input>::SquareWave(NodeHandle& nodeHandle)
: Waveform<Input>(nodeHandle)
{
    nodeHandle.setName("Square wave");
}

template<typename Input>
float SquareWave<Input>::calculate(const FrameContext& frame) const
{
    return this->amplitude(frame) * floor(2 * frame.timeSeconds() * this->frequency(frame) + this->phase(frame));
}
