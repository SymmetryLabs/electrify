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

    void load(unique_ptr<Renderable>&& renderable, unique_ptr<Model>&& model);

    Renderer& getRenderer();
    Model& getModel();
    const DataRelay& getDataRelay() const;
    unsigned int getDataRelayId() const;

    void start();
    void stop();
    void wait();

    void copyColorBuffer(vector<Color>& colorBuffer);
    unsigned int copyColorBuffer(unsigned int id, vector<Color>& colorBuffer);
    void setProfilingEnabled(bool enabled);

    bool shouldStopAfter1Second = false;

    void init();
    void deinit();

    void performFrameUpdate();
    void performRasterization();

private:
    DataRelay& dataRelay;
    unique_ptr<Renderable> renderable;
    unique_ptr<Model> model;

    thread engineThread;
    atomic_flag keepRunning = ATOMIC_FLAG_INIT;
    atomic_bool isRunning;

    bool profilingEnabled = false;

    DoubleBuffer<Color> doubleBuffer;
    Renderer renderer;

    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point currentFrameTime;
    long currentFrameNumber = 0;

    unsigned int dataRelayId = 0;

    void loop();
    void performLoopStep();

};
