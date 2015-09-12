#include "engine.h"

#include "frame_context.h"
#include "event_queue.h"
#include "session.h"
#include "rasterization_thread.h"
#include "project.h"
#include "output.h"
#include "renderable.h"

Engine::Engine()
: rasterizationThread(make_unique<RasterizationThread>(dataBridge.getSlaveRelay()))
{
}

Engine::~Engine() = default;

void Engine::loadProject(unique_ptr<Project>&& project_)
{
    session.project = move(project_);
    Project& project = *session.project;
    rasterizationThread->load(project.releaseRenderable(dataBridge), project.getModel());
}

void Engine::registerOutput(Output& output)
{
    rasterizationThread->registerOutput(output);
}

void Engine::unregisterOutput(Output& output)
{
    rasterizationThread->unregisterOutput(output);
}

void Engine::start()
{
    rasterizationThread->start();
}

void Engine::startAndWait()
{
    rasterizationThread->shouldStopAfter1Second = true;
    rasterizationThread->start();
    rasterizationThread->wait();
}

void Engine::stop()
{
    rasterizationThread->stop();
}

void Engine::stopAndWait()
{
    rasterizationThread->stop();
    rasterizationThread->wait();
}

void Engine::wait()
{
    rasterizationThread->wait();
}

void Engine::setProfilingEnabled(bool enabled)
{
    rasterizationThread->setProfilingEnabled(enabled);
}

DataRelay& Engine::getDataRelay()
{
    return dataBridge.getMasterRelay();
}
