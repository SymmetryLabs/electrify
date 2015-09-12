#pragma once
#include "globals.h"

#include <atomic>
#include <thread>

#include "double_buffer.h"
#include "renderer.h"

class Renderable;
class DataRelay;
class Model;
class Output;

class RasterizationThread {

public:
    explicit RasterizationThread(DataRelay& dataRelay);
    ~RasterizationThread();

    void load(unique_ptr<Renderable>&& renderable, Model& model);

    void registerOutput(Output& output);
    void unregisterOutput(Output& output);

    void start();
    void stop();
    void wait();

    void copyColorBuffer(vector<Color>& colorBuffer);
    void queueEvent(function<void()>* eventFunc);
    void setProfilingEnabled(bool enabled);

    Event<> preFrameUpdateEvent;
    Event<> postFrameUpdateEvent;

    bool shouldStopAfter1Second = false;

private:
    DataRelay& dataRelay;
    unique_ptr<Renderable> renderable;
    Model* model = nullptr;

    thread engineThread;
    atomic_flag keepRunning = ATOMIC_FLAG_INIT;
    atomic_bool isRunning;

    bool profilingEnabled = false;

    DoubleBuffer<Color> doubleBuffer;
    Renderer renderer;

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

};
