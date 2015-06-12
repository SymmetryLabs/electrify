#pragma once
#include "constants.h"

#include <thread>
#include "component.h"
#include "blueprint.h"
#include "model.h"
#include "output.h"

constexpr int fps = 60;
constexpr nanoseconds timePerFrame {duration_cast<nanoseconds>(seconds{1}) / fps};

/**
 * The engine loads networks of Components and also keeps time
 */
class Engine {

public:
  Engine(unique_ptr<Blueprint> blueprint_, unique_ptr<Model> model_);
  virtual ~Engine() {}

  void start();
  void startAndWait();
  void stop();

  void copyColorBuffer(vector<Color>& colorBuffer);

private:
  const unique_ptr<Blueprint> blueprint;
  const unique_ptr<Model> model;

  thread engineThread;

  unique_ptr<vector<Color>> frontColorBuffer;
  unique_ptr<vector<Color>> backColorBuffer;
  mutex colorBufferMutex;

  high_resolution_clock::time_point startTime;
  high_resolution_clock::time_point currentFrameTime;
  long currentFrameNumber;

  void init();
  void loop();
  void performLoopStep();
  void performFrameUpdate();
  void performRasterization();

  inline void swapColorBuffers();
  inline unique_lock<mutex> acquireColorBufferLock();

};
