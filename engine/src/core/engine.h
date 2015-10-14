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

/**
 * The engine loads networks of Nodes and also keeps time
 */
class Engine : public DataTransmitter {

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

    void setProfilingEnabled(bool enabled);

    DataRelay& getDataRelay();

private:

    Session session;
    DataBridge dataBridge;
    shared_ptr<RasterizationThread> rasterizationThread;

    void notifyProjectChanged(Project& project);

    friend class Session;

};
