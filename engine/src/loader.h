#pragma once
#include "constants.h"

#include <fstream>
#include <json/json-forwards.h>
#include <json/json.h>
#include "model.h"

class Loader {
public:
  unique_ptr<Model> loadJSON(string filename);
};
