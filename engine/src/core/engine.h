#pragma once
#include "globals.h"

#include "session.h"
#include "data_bridge.h"
#include "data_transmitter.h"

constexpr static int FPS = 60;
constexpr static nanoseconds TIME_PER_FRAME {duration_cast<nanoseconds>(seconds{1}) / FPS};

class Output;
class Project;
class DataRelay;
class RasterizationThread;
class Renderer;

/**
 * The engine loads networks of Nodes and also keeps time
 */
class Engine {

public:
    Engine();
    ~Engine();

    Session& getSession();

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
    DataTransmitter dataTransmitter;
    shared_ptr<RasterizationThread> rasterizationThread;
    Renderer& renderer;

    void notifyProjectChanged(Project& project);

    friend class Session;

};
