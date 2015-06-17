#pragma once
#include "constants.h"

#include <atomic>
#include <thread>
#include <boost/lockfree/queue.hpp>

#include "component.h"
#include "renderable.h"
#include "model.h"
#include "output.h"

constexpr static int FPS = 60;
constexpr static nanoseconds TIME_PER_FRAME {duration_cast<nanoseconds>(seconds{1}) / FPS};

/**
 * The engine loads networks of Components and also keeps time
 */
class Engine {

public:
  Engine(unique_ptr<Renderable> renderable_, unique_ptr<Model> model_);
  virtual ~Engine() {}

  void start();
  void startAndWait();

  void stop();
  void stopAndWait();

  void copyColorBuffer(vector<Color>& colorBuffer);

private:
  const unique_ptr<Renderable> renderable;
  const unique_ptr<Model> model;

  atomic_flag keepRunning;

  thread engineThread;
  boost::lockfree::queue<function<void()>*> internalEventQueue;
  bool shouldStopAfter2Seconds = false;

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

  inline void swapColorBuffers();

};
