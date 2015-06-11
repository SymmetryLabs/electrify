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
  Engine(shared_ptr<Blueprint> blueprint_, shared_ptr<Model> model_);
  virtual ~Engine() {}

  void start();
  void startAndWait();
  void stop();

  void copyColorBuffer(vector<Color> &colorBuffer);

  vector<shared_ptr<Output>> outputs;

private:
  shared_ptr<Blueprint> blueprint;
  shared_ptr<Model> model;

  thread engineThread;
  shared_ptr<vector<Color>> frontColorBuffer;
  shared_ptr<vector<Color>> backColorBuffer;
  mutex colorBufferMutex;

  high_resolution_clock::time_point startTime;
  high_resolution_clock::time_point currentFrameTime;
  long currentFrameNumber;

  void init();
  void loop();
  void performLoopStep();
  void performFrameUpdate();
  void performRasterization();

  void swapColorBuffers();
  unique_lock<mutex> acquireColorBufferLock();

};
