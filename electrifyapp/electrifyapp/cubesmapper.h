#ifndef CUBESMAPPER_H
#define CUBESMAPPER_H
#include <unordered_map>
#include "group.h"
#include "pixel.h"
#include "model.h"
#include "cubesmapper.h"
#include "cubesmodel.h"

class CubesMapper
{
public:
    CubesMapper();
    ~CubesMapper();
    void map_cube(string id, int boardNum, int pinNum, CubesModel *model);
    int getOutputIndex(Pixel p);
    int nPointsPerPin = 256;
    int STRIP_ORD[16] = {10,  9, 12, 6 , 5, 8, 7, 11, 15, 3, 2, 1,  4, 14, 13, 16 };
    //unordered_map<string,vector<int,int>> cubemapping;
    unordered_map<int,int> pixelmapping;
};

#endif // CUBESMAPPER_H
