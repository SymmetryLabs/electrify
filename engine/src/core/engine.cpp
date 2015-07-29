#include "engine.h"

#include "frame_context.h"

using namespace boost;

Engine::Engine(std::shared_ptr<Renderable> renderable_, unique_ptr<Model> model_)
  : renderable(renderable_)
  , model(move(model_))
  , keepRunning(ATOMIC_FLAG_INIT)
  , internalEventQueue(10)
{
  frontColorBuffer = make_unique<vector<Color>>(model->pixels.size());
  backColorBuffer = make_unique<vector<Color>>(model->pixels.size());
}

void Engine::start()
{
  cout << "Starting Engine" << endl;
  keepRunning.test_and_set();
  isRunning = true;
  engineThread = thread(&Engine::loop, this);
}

void Engine::startAndWait()
{
  shouldStopAfter2Seconds = true;
  start();
  engineThread.join();
}

void Engine::stop()
{
  keepRunning.clear();
}

void Engine::stopAndWait()
{
  stop();
  engineThread.join();
}

void Engine::init()
{
  startTime = high_resolution_clock::now();
  currentFrameTime = startTime;
  currentFrameNumber = 0;

  renderable->initRenderable(*model);
}

void Engine::deinit()
{
  renderable->deinitRenderable();
  isRunning = false;
  processQueuedEvents();
  cout << "Engine stopped" << endl;
}

void Engine::loop()
{
  init();
  while (keepRunning.test_and_set()) {

    performLoopStep();

    auto nextFrameTime = currentFrameTime + TIME_PER_FRAME;

    if (profilingEnabled) {
      cout << "Spare cycle time: "
        << duration_cast<milliseconds>(nextFrameTime - high_resolution_clock::now()).count()
        << "ms" << endl;
    }

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

    if (shouldStopAfter2Seconds && currentFrameNumber > 100) {
      stop();
    }

    // poll events
  }
  deinit();
}

void Engine::performLoopStep()
{
  high_resolution_clock::time_point loopStepStartTime = high_resolution_clock::now();

  // calculate how many frames we're going to catch up by
  auto loopTimeDelta = high_resolution_clock::now() - currentFrameTime;
  // limit catchup updates to 250ms total per loop step
  constexpr auto maxLoopTimeDelta = duration_cast<nanoseconds>(milliseconds{250});
  if (loopTimeDelta > maxLoopTimeDelta) {
    loopTimeDelta = maxLoopTimeDelta;
  } else if (loopTimeDelta < TIME_PER_FRAME) {
    // don't do any processing if we've been called too soon
    return;
  }

  // perform as many update loops as we need (within reason)
  while (loopTimeDelta >= TIME_PER_FRAME) {
    auto beginUpdateTime = high_resolution_clock::now();

    preFrameUpdateEvent();

    processQueuedEvents();
    performFrameUpdate();

    postFrameUpdateEvent();

    loopTimeDelta -= TIME_PER_FRAME;

    // Prevent runaway updates if updates take longer than a frame
    if (high_resolution_clock::now() - beginUpdateTime >= TIME_PER_FRAME) {
      break;
    }
  }

  performRasterization();

  if (profilingEnabled) {
    cout << "Loop time: "
      << duration_cast<milliseconds>(high_resolution_clock::now() - loopStepStartTime).count()
      << "ms" << endl;
  }
}

void Engine::performFrameUpdate()
{
  currentFrameTime += TIME_PER_FRAME;
  currentFrameNumber++;

  FrameContext frameContext(currentFrameTime - startTime);
  renderable->updateRenderable(frameContext);
}

void Engine::performRasterization()
{
  FrameContext frameContext(currentFrameTime - startTime);
  renderable->renderRenderable(frameContext, *backColorBuffer.get());

  swapColorBuffers();

  // TODO: send color buffer changed notification
}

void Engine::queueEvent(function<void()>* eventFunc)
{
  internalEventQueue.push(eventFunc);

  if (!isRunning) {
    processQueuedEvents();
  }
}

void Engine::processQueuedEvents()
{
  function<void()>* eventFunc;
  while (internalEventQueue.pop(eventFunc)) {
    (*eventFunc)();
    delete eventFunc;
  }
}

void Engine::setProfilingEnabled(bool enabled)
{
  profilingEnabled = enabled;
}

void Engine::copyColorBuffer(vector<Color>& colorBuffer)
{
  lock_guard<mutex> lock {colorBufferMutex};

  colorBuffer = *frontColorBuffer;
}

void Engine::swapColorBuffers()
{
  lock_guard<mutex> lock {colorBufferMutex};

  swap(backColorBuffer, frontColorBuffer);
}
