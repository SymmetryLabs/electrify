#ifndef CUBESMODEL_H
#define CUBESMODEL_H
#include "model.h"
#include "group.h"
#include <unordered_map>

class CubesModel : public Model
{
public:
    unordered_map<string, Group*> cubesByID;
    CubesModel(Model *m);
    ~CubesModel();
};

#endif // CUBESMODEL_H
