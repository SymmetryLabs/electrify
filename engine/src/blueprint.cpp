#include "blueprint.h"

Blueprint::Blueprint()
{
  output = registerWirableOutput<Color>("color");
}

void Blueprint::initRenderable(const Model& model_)
{
  init();
  model = &model_;
}

void Blueprint::deinitRenderable()
{
  deinit();
  model = nullptr;
}

void Blueprint::updateRenderable(const FrameContext& frame)
{
  update(frame);
}

void Blueprint::renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer)
{
  // rasterize to color buffer
  int i = 0;
  for (const auto& pixel : model->pixels) {
    FragmentContext frag(pixel);
    colorBuffer[i++] = output->calculate(frag);
  }
}
