#pragma once
#include "globals.h"

#include "json/json-forwards.h"

class Model;
// class Group;
class Pixel;

class Loader {

public:
    unique_ptr<Model> loadJSON(string filename);
    // shared_ptr<Group> parseGroup(Json::Value val, ObservableVector<shared_ptr<Pixel>>& pixels, shared_ptr<Group> parent);
    // shared_ptr<Pixel> parsePixelReference(Json::Value val, ObservableVector<shared_ptr<Pixel>>& pixels, shared_ptr<Group> parent);

};
