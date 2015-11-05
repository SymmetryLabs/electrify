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
class ProxySlaveVisitor;

/**
 * The engine loads networks of Nodes and also keeps time
 */
class Engine {

public:
    Engine();
    ~Engine();

    Session& getSession();

    void loadProject(unique_ptr<Project>&& project);

    void registerOutput(const shared_ptr<Output>& output);
    void unregisterOutput(const shared_ptr<Output>& output);

    void start();
    void startAndWait();

    void stop();
    void stopAndWait();

    void wait();

    void init();
    void deinit();

    void setProfilingEnabled(bool enabled);

    DataRelay& getDataRelay();
    RasterizationThread& getRasterizationThread();

private:
    Session session;
    bool inited;

    DataBridge dataBridge;
    DataTransmitter dataTransmitter;

    shared_ptr<RasterizationThread> rasterizationThread;
    shared_ptr<ProxySlaveVisitor> proxySlaveVisitor;
    Renderer& renderer;

    vector<shared_ptr<Output>> outputs;
    vector<shared_ptr<ProxySlaveVisitor>> outputModelVisitors;

    void notifyProjectChanged(Project& project);

    void setModelForOutput(const shared_ptr<Output>& output);
    void resetModelForOutputs();

    friend class Session;

};
