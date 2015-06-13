#pragma once
#include "constants.h"

#include "compound_component.h"
#include "renderable.h"
#include "socket.h"

class Blueprint : public CompoundComponent, public Renderable {

public:
  Blueprint();
  virtual ~Blueprint() {}

  virtual void initRenderable(const Model& model_) override;
  virtual void deinitRenderable() override;
  virtual void updateRenderable(const FrameContext& frame) override;
  virtual void renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer) override;

private:
  Socket<Color>* output;
  const Model* model;

};
