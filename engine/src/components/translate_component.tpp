template <typename V>
TranslateComponent<V>::TranslateComponent()
{
  registerInput("signalInput", &signalInput);
  registerInput("translateX", &translateX);
  registerInput("translateY", &translateY);
  registerInput("translateZ", &translateZ);
}

template <typename V>
V TranslateComponent<V>::calculate(const FrameContext& frame) const
{
  Pixel pixel {frame.frag->pixel};
  pixel.x += translateX(frame);
  pixel.y += translateY(frame);
  pixel.z += translateZ(frame);
  
  FragmentContext frag(pixel);
  FrameContext childFrame(frame, &frag);
  return signalInput(childFrame);
}
