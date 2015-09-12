#pragma once
#include "globals.h"

#include "session.h"
#include "data_bridge.h"

constexpr static int FPS = 60;
constexpr static nanoseconds TIME_PER_FRAME {duration_cast<nanoseconds>(seconds{1}) / FPS};

class Output;
class project;
class DataRelay;
class RasterizationThread;

/**
 * The engine loads networks of Nodes and also keeps time
 */
class Engine {

public:
    Engine();
    ~Engine();

    void loadProject(unique_ptr<Project>&& project);

    void registerOutput(Output& output);
    void unregisterOutput(Output& output);

    void start();
    void startAndWait();

    void stop();
    void stopAndWait();

    void wait();

    void setProfilingEnabled(bool enabled);

    DataRelay& getDataRelay();

private:

    Session session;
    DataBridge dataBridge;
    unique_ptr<RasterizationThread> rasterizationThread;

};
