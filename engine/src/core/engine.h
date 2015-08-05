#pragma once

#include <atomic>
#include <thread>
#include <mutex>

#include <boost/lockfree/queue.hpp>

#include "globals.h"

#include "renderable.h"
#include "model.h"
#include "event_queue.h"

constexpr static int FPS = 60;
constexpr static nanoseconds TIME_PER_FRAME {duration_cast<nanoseconds>(seconds{1}) / FPS};

/**
 * The engine loads networks of Nodes and also keeps time
 */
class Engine {

  USING_REACTIVE_DOMAIN(EngineDomain)

public:
  Engine(shared_ptr<Renderable> renderable, unique_ptr<Model> model);
  virtual ~Engine();

  void start();
  void startAndWait();

  void stop();
  void stopAndWait();

  void wait();

  void copyColorBuffer(vector<Color>& colorBuffer);

  void queueEvent(function<void()>* eventFunc);

  void setProfilingEnabled(bool enabled);

  shared_ptr<Renderable> getRenderable() { return renderable; }
  Model* getModel() { return model.get(); }

  EventSourceT<> preFrameUpdateEvent = MakeEventSource<EngineDomain>();
  EventSourceT<> postFrameUpdateEvent = MakeEventSource<EngineDomain>();

private:
  std::shared_ptr<Renderable> renderable;
  unique_ptr<Model> model;

  thread engineThread;
  atomic_flag keepRunning;
  atomic_bool isRunning;

  bool profilingEnabled = false;
  bool shouldStopAfter2Seconds = false;

  boost::lockfree::queue<function<void()>*> internalEventQueue;

  unique_ptr<vector<Color>> frontColorBuffer;
  unique_ptr<vector<Color>> backColorBuffer;
  mutex colorBufferMutex;

  high_resolution_clock::time_point startTime;
  high_resolution_clock::time_point currentFrameTime;
  long currentFrameNumber = 0;

  void init();
  void deinit();

  void loop();
  void performLoopStep();

  void performFrameUpdate();
  void performRasterization();
  void processQueuedEvents();

  inline void swapColorBuffers();

};
