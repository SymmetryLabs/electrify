#pragma once
#include "constants.h"

#include <fstream>
#include <json/json-forwards.h>
#include <json/json.h>
#include "model.h"
#include "group.h"
#include "pixel.h"

class Loader {
public:
  unique_ptr<Model> loadJSON(string filename);
  Group* parseGroup(Json::Value val, vector<Pixel*> *pixels, Group *parent);
  Pixel* parsePixelReference(Json::Value val, vector<Pixel*> *pixels, Group *parent);
};
