#include "engine.h"

#include "frame_context.h"
#include "fragment_context.h"

Engine::Engine(shared_ptr<Blueprint> blueprint_, shared_ptr<Model> model_)
:blueprint(blueprint_)
,model(model_)
,frontColorBuffer(make_shared<vector<Color>>(model_->pixels.size()))
,backColorBuffer(make_shared<vector<Color>>(model_->pixels.size())) {
}

void Engine::start() {
  cout << "Starting Engine";
  engineThread = thread(&Engine::loop, this);
  engineThread.join();
}

void Engine::stop() {
}

void Engine::loop() {
  while (true) {
    FrameContext frameContext;

    // update components
    for (auto component : blueprint->components) {
      component->update(frameContext);
    }

    // rasterize to color buffer
    int i = 0;
    for (auto pixel : model->pixels) {
      FragmentContext fragmentContext(pixel);
      auto color = blueprint->outputSocket.input_signal->calculate_function(frameContext);
      (*backColorBuffer)[i] = color;
      i++;
    }

    swapColorBuffers();

    // send color buffer changed notification

    // poll events
  }
}

void Engine::copyColorBuffer(vector<Color> &colorBuffer) {
  unique_lock<mutex> lock = acquireColorBufferLock();

  colorBuffer = {*frontColorBuffer};
}

void Engine::swapColorBuffers() {
  unique_lock<mutex> lock = acquireColorBufferLock();

  shared_ptr<vector<Color>> tempColorBuffer = frontColorBuffer;
  frontColorBuffer = backColorBuffer;
  backColorBuffer = tempColorBuffer;
}

unique_lock<mutex> Engine::acquireColorBufferLock() {
  return unique_lock<mutex> {colorBufferMutex};
}
