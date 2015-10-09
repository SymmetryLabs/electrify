#include "rasterization_thread.h"

#include <assert.h>

#include "output.h"
#include "renderable.h"
#include "data_relay.h"
#include "engine.h"
#include "model.h"
#include "frame_context.h"

RasterizationThread::RasterizationThread(DataRelay& dataRelay_)
: dataRelay(dataRelay_)
, isRunning(false)
, renderer(doubleBuffer)
{
}

RasterizationThread::~RasterizationThread()
{
    stop();
    wait();
}

void RasterizationThread::load(unique_ptr<Renderable>&& renderable_, Model& model_)
{
    model = &model_;
    renderable = move(renderable_);

    doubleBuffer.setSize(model->pixels.size());
}

void RasterizationThread::registerOutput(Output& output)
{
    output.setRenderer(&renderer);
}

void RasterizationThread::unregisterOutput(Output& output)
{
    output.setRenderer(nullptr);
}

void RasterizationThread::start()
{
    assert(!isRunning);

    cout << "Starting Engine" << endl;
    keepRunning.test_and_set();
    isRunning = true;
    engineThread = thread(&RasterizationThread::loop, this);
}

void RasterizationThread::stop()
{
    keepRunning.clear();
}

void RasterizationThread::wait()
{
    if (engineThread.joinable()) {
        engineThread.join();
    }
}

void RasterizationThread::init()
{
    startTime = high_resolution_clock::now();
    currentFrameTime = startTime;
    currentFrameNumber = 0;

    renderable->initRenderable(*model);
}

void RasterizationThread::deinit()
{
    renderable->deinitRenderable();
    isRunning = false;
    cout << "Engine stopped" << endl;
}

void RasterizationThread::loop()
{
    init();
    while (keepRunning.test_and_set()) {

        performLoopStep();

        auto nextFrameTime = currentFrameTime + TIME_PER_FRAME;

        if (profilingEnabled) {
            cout << "Spare cycle time: "
                << duration_cast<milliseconds>(nextFrameTime - high_resolution_clock::now()).count()
                << "ms" << endl;
        }

        constexpr static bool USE_IDLE_LOOP = false;
        if (USE_IDLE_LOOP) {
            while (nextFrameTime > high_resolution_clock::now()) {
            }
        } else {
            if (nextFrameTime > high_resolution_clock::now()) {
                this_thread::sleep_until(nextFrameTime);
            }
        }
        // auto wakeupOffBy = high_resolution_clock::now() - nextFrameTime;
        // cout << "cycle " << duration_cast<nanoseconds>(wakeupOffBy).count() << endl;

        if (shouldStopAfter1Second && currentFrameNumber > 30) {
            stop();
        }

        // poll events
    }
    deinit();
}

void RasterizationThread::performLoopStep()
{
    high_resolution_clock::time_point loopStepStartTime = high_resolution_clock::now();

    // calculate how many frames we're going to catch up by
    auto loopTimeDelta = high_resolution_clock::now() - currentFrameTime;
    // limit catchup updates to 250ms total per loop step
    constexpr auto maxLoopTimeDelta = duration_cast<nanoseconds>(milliseconds{250});
    if (loopTimeDelta > maxLoopTimeDelta) {
        loopTimeDelta = maxLoopTimeDelta;
    } else if (loopTimeDelta < TIME_PER_FRAME) {
        // don't do any processing if we've been called too soon
        return;
    }

    // perform as many update loops as we need (within reason)
    while (loopTimeDelta >= TIME_PER_FRAME) {
        auto beginUpdateTime = high_resolution_clock::now();

        dataRelay.processIncomingTransactions();

        performFrameUpdate();

        dataRelay.commitOutgoingTransaction();

        loopTimeDelta -= TIME_PER_FRAME;

        // Prevent runaway updates if updates take longer than a frame
        if (high_resolution_clock::now() - beginUpdateTime >= TIME_PER_FRAME) {
            break;
        }
    }

    performRasterization();

    if (profilingEnabled) {
        cout << "Loop time: "
            << duration_cast<milliseconds>(high_resolution_clock::now() - loopStepStartTime).count()
            << "ms" << endl;
    }
}

void RasterizationThread::performFrameUpdate()
{
    currentFrameTime += TIME_PER_FRAME;
    currentFrameNumber++;

    FrameContext frameContext(currentFrameTime - startTime);
    renderable->updateRenderable(frameContext);
}

void RasterizationThread::performRasterization()
{
    FrameContext frameContext(currentFrameTime - startTime);
    renderable->renderRenderable(frameContext, doubleBuffer.getBackBuffer());

    doubleBuffer.swapBuffers();

    // TODO: send color buffer changed notification
}

void RasterizationThread::setProfilingEnabled(bool enabled)
{
    profilingEnabled = enabled;
}

void RasterizationThread::copyColorBuffer(vector<Color>& colorBuffer)
{
    doubleBuffer.copyBuffer(colorBuffer);
}
