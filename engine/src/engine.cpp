#include "engine.h"

#include "frame_context.h"

Engine::Engine(shared_ptr<Blueprint> blueprint_)
:blueprint(blueprint_)
{
}

void Engine::start()
{
  cout << "Starting Engine";
  while (true) {
    FrameContext frameContext;
    for (auto c : blueprint->components) {
      c->update(frameContext);
    }
    // draw
    // poll events
  }
}

void Engine::stop()
{

}
