#pragma once
#include "globals.h"

#include "model.h"
#include "data_relay.h"

class Renderer;
class Color;
class ProxySlaveVisitor;
class OutgoingDataRelay;

class Output : public std::enable_shared_from_this<Output> {

public:
    Output();
    ~Output();

    bool hasRenderer() const;
    void setRenderer(Renderer* renderer);

    bool hasModel() const;
    Model& getModel();
    const ObservableSharedPtr<Model>& getModelObservable() const;
    void setModel(const shared_ptr<Model>& model);

    void populateFrame();
    unsigned int getLastFrameId() const;

    const vector<Color>& getColorBuffer() const;

    OutgoingDataRelay& getOutgoingDataRelay();

// private:
    vector<Color> colorBuffer;

    Renderer* renderer = nullptr;
    ObservableSharedPtr<Model> model;

    DataRelay dataRelay;
    unsigned int lastFrameId = -1;

};
