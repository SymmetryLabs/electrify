#include "cubesmodel.h"

CubesModel::CubesModel(Model *m)
{
    for(size_t towerindex=0; towerindex< m->root->members->size(); towerindex++)
    {
        Group *tower =  (*m->root->members)[towerindex];
        for(int cubeindex=0; cubeindex<tower->members->size(); cubeindex++)
        {
            Group *cube = (*tower->members)[cubeindex];
            cubesByID[cube->id] = cube;
        }
    }
}

CubesModel::~CubesModel()
{

}

