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
#include "model_visitor.h"
#include "proxy_slave_visitor.h"

Engine::Engine()
: session{*this}
, inited(false)
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
    if (session.hasProject()) {
        proxySlaveVisitor->remove(session.getModel());
    }
    session.setProject(forward<unique_ptr<Project>>(project));
}

void Engine::registerOutput(const shared_ptr<Output>& output)
{
    output->setRenderer(&renderer);
    setModelForOutput(output);
    getDataRelay().addAuxOutgoingDataRelay(output->getOutgoingDataRelay());
    outputs.push_back(output);
}

void Engine::unregisterOutput(const shared_ptr<Output>& output)
{
    output->setRenderer(nullptr);
    getDataRelay().removeAuxOutgoingDataRelay(output->getOutgoingDataRelay());
    removeSharedPtr(outputs, output.get());
}

void Engine::start()
{
    init();
    rasterizationThread->start();
}

void Engine::startAndWait()
{
    init();
    rasterizationThread->shouldStopAfter1Second = true;
    rasterizationThread->start();
    rasterizationThread->wait();
}

void Engine::stop()
{
    deinit();
    rasterizationThread->stop();
}

void Engine::stopAndWait()
{
    deinit();
    rasterizationThread->stop();
    rasterizationThread->wait();
}

void Engine::wait()
{
    rasterizationThread->wait();
}

void Engine::init()
{
    dataTransmitter.setDataProxies(dataBridge.getMasterProxy(), dataBridge.getSlaveProxy());
    inited = true;
}

void Engine::deinit()
{
    inited = false;
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

RasterizationThread& Engine::getRasterizationThread()
{
    return *rasterizationThread;
}

void Engine::notifyProjectChanged(Project& project)
{
    resetModelForOutputs();

    auto renderable = ReleasableSharedPtr<Renderable>(project.releaseRenderable(dataBridge));
    auto& model = project.getModel();
    auto slaveModel = ReleasableSharedPtr<Model>(std::make_unique<Model>());
    proxySlaveVisitor = std::make_shared<ProxySlaveVisitor>(dataBridge.getMasterProxy());
    (*proxySlaveVisitor)(model, *slaveModel);
    dataTransmitter.sendCommand<RasterizationThread>([=] (const shared_ptr<RasterizationThread>& rt) {
        rt->load(renderable.release(), slaveModel.release());
    });
}

void Engine::setModelForOutput(const shared_ptr<Output>& output)
{
    if (session.hasProject()) {
        auto newModel = make_shared<Model>();
        auto visitor = make_shared<ProxySlaveVisitor>(output->getOutgoingDataRelay().getProxy());
        (*visitor)(session.getModel(), *newModel);
        outputModelVisitors.push_back(visitor);

        if (inited) {
            output->getOutgoingDataRelay().getProxy().sendEvent([=] (const shared_ptr<Output>& output) {
                output->setModel(newModel);
            }, output);
        } else {
            output->setModel(newModel);
        }
    }
}

void Engine::resetModelForOutputs()
{
    outputModelVisitors.clear();
    for (const auto& output : outputs) {
        setModelForOutput(output);
    }
}
