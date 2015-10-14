#include "engine.h"

#include "frame_context.h"
#include "event_queue.h"
#include "session.h"
#include "rasterization_thread.h"
#include "project.h"
#include "output.h"
#include "renderable.h"

Engine::Engine()
: session{*this}
, rasterizationThread(make_shared<RasterizationThread>(dataBridge.getSlaveRelay()))
{
    setDestination(rasterizationThread);
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

void Engine::registerOutput(const shared_ptr<Output>& output)
{

    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt, const shared_ptr<Output>& o) {
        rt->registerOutput(*o);
    }, weak_ptr<Output>(output));
}

void Engine::unregisterOutput(const shared_ptr<Output>& output)
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt, const shared_ptr<Output>& o) {
        rt->unregisterOutput(*o);
    }, weak_ptr<Output>(output));
}

void Engine::start()
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->start();
    });
}

void Engine::startAndWait()
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->shouldStopAfter1Second = true;
        rt->start();
        rt->wait();
    });
}

void Engine::stop()
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->stop();
    });
}

void Engine::stopAndWait()
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->stop();
        rt->wait();
    });
}

void Engine::wait()
{
    sendCommand<RasterizationThread>([] (const shared_ptr<RasterizationThread>& rt) {
        rt->wait();
    });
}

void Engine::setProfilingEnabled(bool enabled)
{
    sendCommand<RasterizationThread>([=] (const shared_ptr<RasterizationThread>& rt) {
        rt->setProfilingEnabled(enabled);
    });
}

DataRelay& Engine::getDataRelay()
{
    return dataBridge.getMasterRelay();
}

void Engine::notifyProjectChanged(Project& project)
{
    auto renderable = project.releaseRenderable(dataBridge);
    // auto cmd = [&] (const shared_ptr<RasterizationThread>& rt,
    //     unique_ptr<Renderable>& renderable)
    // {
    //     rt->load(move(renderable), project.getModel());
    // };
    // auto boundCmd = bind(cmd, placeholders::_1, project.releaseRenderable(dataBridge));
    // sendCommand<RasterizationThread>(boundCmd);
    rasterizationThread->load(move(renderable), project.getModel());
}
