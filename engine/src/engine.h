#pragma once
#include "constants.h"

#include "component.h"
#include "blueprint.h"
#include "model.h"
#include "output.h"

/**
 * The engine loads networks of Components and also keeps time
 */
class Engine {

public:
  Engine(shared_ptr<Blueprint> blueprint_, shared_ptr<Model> model_);
  virtual ~Engine() {}

  void start();
  void stop();

  vector<shared_ptr<Output>> outputs;

private:
  shared_ptr<Blueprint> blueprint;
  shared_ptr<Model> model;
  vector<Color> colorBuffer;

};
