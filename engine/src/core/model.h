#pragma once
#include "globals.h"

class Pixel;
// class Group;
class DataProxy;

class Model {

public:
    ObservableVector<shared_ptr<Pixel>> pixels;
    // ObservableSharedPtr<Group> root;

    size_t getNumPixels() const;

    template <typename Visitor, typename... ModelType,
        typename enable_if_all<int, are_same<Model, typename std::decay<ModelType>::type...>::value>::type>
    friend void performOnObjects(Visitor& visitor, ModelType&&... modelObjects);

};
