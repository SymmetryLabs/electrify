#include "output.h"

#include "color.h"
#include "renderer.h"
#include "proxy_slave_visitor.h"
#include "model_visitor.h"
#include "outgoing_data_relay.h"

Output::Output() = default;
Output::~Output() = default;

bool Output::hasRenderer() const
{
    return static_cast<bool>(renderer);
}

void Output::setRenderer(Renderer* renderer_)
{
    renderer = renderer_;
}

bool Output::hasModel() const
{
    return static_cast<bool>(model);
}

Model& Output::getModel()
{
    return *model;
}

const ObservableSharedPtr<Model>& Output::getModelObservable() const
{
    return model;
}

void Output::setModel(const shared_ptr<Model>& model_)
{
    model = model_;
}

void Output::populateFrame()
{
    if (renderer) {
        unsigned int rendererFrameId;
        while ((rendererFrameId = renderer->copyColorBuffer(lastFrameId, colorBuffer)) != lastFrameId) {
            dataRelay.processIncomingTransactionsUpTo(rendererFrameId);
            lastFrameId = rendererFrameId;
            if (model && colorBuffer.size() != model->getNumPixels()) {
                colorBuffer.resize(model->getNumPixels());
            }
        }
    }
}

unsigned int Output::getLastFrameId() const
{
    return lastFrameId;
}

const vector<Color>& Output::getColorBuffer() const
{
    return colorBuffer;
}

OutgoingDataRelay& Output::getOutgoingDataRelay()
{
    return dataRelay.getOutgoingDataRelay();
}
