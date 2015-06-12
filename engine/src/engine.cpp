#include "engine.h"

#include "frame_context.h"
#include "fragment_context.h"

Engine::Engine(unique_ptr<Blueprint> blueprint_, unique_ptr<Model> model_)
  :blueprint(move(blueprint_))
  ,model(move(model_))
{
  frontColorBuffer = unique_ptr<vector<Color>> {new vector<Color>(model->pixels.size())};
  backColorBuffer = unique_ptr<vector<Color>> {new vector<Color>(model->pixels.size())};
}

void Engine::start()
{
  cout << "Starting Engine" << endl;
  engineThread = thread(&Engine::loop, this);
}

void Engine::startAndWait()
{
  start();
  engineThread.join();
}

void Engine::stop()
{
}

void Engine::init()
{
  startTime = high_resolution_clock::now();
  currentFrameTime = startTime;
  currentFrameNumber = 0;

  blueprint->init();
}

void Engine::loop()
{
  init();
  while (true) {
    performLoopStep();

    auto nextFrameTime = currentFrameTime + timePerFrame;
    constexpr static bool USE_IDLE_LOOP = false;
    if (USE_IDLE_LOOP) {
      while (nextFrameTime > high_resolution_clock::now()) {
      }
    } else {
      if (nextFrameTime > high_resolution_clock::now()) {
        this_thread::sleep_until(nextFrameTime);
      }
    }
    // auto wakeupOffBy = high_resolution_clock::now() - nextFrameTime;
    // cout << "cycle " << duration_cast<nanoseconds>(wakeupOffBy).count() << endl;

    // if (currentFrameNumber > 100) {
    //   break;
    // }

    // poll events
  }
}

void Engine::performLoopStep()
{
  // calculate how many frames we're going to catch up by
  auto loopTimeDelta = high_resolution_clock::now() - currentFrameTime;
  // limit catchup updates to 250ms total per loop step
  constexpr auto maxLoopTimeDelta = duration_cast<nanoseconds>(milliseconds{250});
  if (loopTimeDelta > maxLoopTimeDelta) {
    loopTimeDelta = maxLoopTimeDelta;
  } else if (loopTimeDelta < timePerFrame) {
    // don't do any processing if we've been called too soon
    return;
  }

  // perform as many update loops as we need (within reason)
  while (loopTimeDelta >= timePerFrame) {
    auto beginUpdateTime = high_resolution_clock::now();

    performFrameUpdate();

    loopTimeDelta -= timePerFrame;

    // Prevent runaway updates if updates take longer than a frame
    if (high_resolution_clock::now() - beginUpdateTime >= timePerFrame) {
      break;
    }
  }

  performRasterization();
}

void Engine::performFrameUpdate()
{
  FrameContext frameContext;

  // update components
  blueprint->update(frameContext);

  currentFrameTime += timePerFrame;
  currentFrameNumber++;
}

void Engine::performRasterization()
{
  FrameContext frameContext;

  // rasterize to color buffer
  int i = 0;
  for (const auto& pixel : model->pixels) {
    FragmentContext fragmentContext(pixel);
    (*backColorBuffer)[i++] = blueprint->render(fragmentContext);
  }

  swapColorBuffers();

  // send color buffer changed notification
}

void Engine::copyColorBuffer(vector<Color>& colorBuffer)
{
  unique_lock<mutex> lock = acquireColorBufferLock();

  colorBuffer = {*frontColorBuffer};
}

void Engine::swapColorBuffers()
{
  unique_lock<mutex> lock = acquireColorBufferLock();

  swap(backColorBuffer, frontColorBuffer);
}

inline unique_lock<mutex> Engine::acquireColorBufferLock()
{
  return unique_lock<mutex> {colorBufferMutex};
}
