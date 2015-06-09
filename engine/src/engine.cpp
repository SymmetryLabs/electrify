#include "engine.h"

#include "frame_context.h"
#include "fragment_context.h"

Engine::Engine(shared_ptr<Blueprint> blueprint_, shared_ptr<Model> model_)
:blueprint(blueprint_)
,model(model_)
,colorBuffer(model_->pixels.size())
{
}

void Engine::start()
{
  cout << "Starting Engine";
  while (true) {
    FrameContext frameContext;

    // update components
    for (auto component : blueprint->components) {
      component->update(frameContext);
    }

    // rasterize color buffer
    int i = 0;
    for (auto pixel : model->pixels) {
      FragmentContext fragmentContext(pixel);
      auto color = blueprint->outputSocket.input_signal->calculate_function(frameContext);
      colorBuffer[i] = color;
      i++;
    }

    // send to outputs
    for (auto output : outputs) {
      output->render(colorBuffer);
    }

    // poll events
  }
}

void Engine::stop()
{
}
