#include "engine.h"

#include "frame_context.h"
#include "event_queue.h"
#include "session.h"
#include "rasterization_thread.h"
#include "project.h"
#include "output.h"
#include "renderable.h"
#include "model.h"
#include "releasable_shared_ptr.h"

Engine::Engine()
: session{*this}
, rasterizationThread(make_shared<RasterizationThread>(dataBridge.getSlaveRelay()))
, renderer(rasterizationThread->getRenderer())
{
    dataTransmitter = DataTransmitter(rasterizationThread);
}

Engine::~Engine() = default;

Session& Engine::getSession()
{
    return session;
}

void Engine::loadProject(unique_ptr<Project>&& project)
{
    session.setProject(forward<unique_ptr<Project>>(project));
}

void Engine::registerOutput(Output& output)
{
    output.setRenderer(&renderer);
}

void Engine::unregisterOutput(Output& output)
{
    output.setRenderer(nullptr);
}

void Engine::start()
{
    dataTransmitter.sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->start();
    });
}

void Engine::startAndWait()
{
    dataTransmitter.sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->shouldStopAfter1Second = true;
        rt->start();
        rt->wait();
    });
}

void Engine::stop()
{
    dataTransmitter.sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->stop();
    });
}

void Engine::stopAndWait()
{
    dataTransmitter.sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->stop();
        rt->wait();
    });
}

void Engine::wait()
{
    dataTransmitter.sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->wait();
    });
}

void Engine::setProfilingEnabled(bool enabled)
{
    dataTransmitter.sendCommand<RasterizationThread>([=] (const shared_ptr<RasterizationThread>& rt) {
        rt->setProfilingEnabled(enabled);
    });
}

DataRelay& Engine::getDataRelay()
{
    return dataBridge.getMasterRelay();
}

void Engine::notifyProjectChanged(Project& project)
{
    auto renderable = ReleasableSharedPtr<Renderable>(project.releaseRenderable(dataBridge));
    auto& model = project.getModel();
    dataTransmitter.sendCommand<RasterizationThread>([=, &model] (const shared_ptr<RasterizationThread>& rt) {
        rt->load(renderable.release(), model);
    });
}
