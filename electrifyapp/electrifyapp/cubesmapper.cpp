#include "cubesmapper.h"

CubesMapper::CubesMapper()
{

}

CubesMapper::~CubesMapper()
{

}

void CubesMapper::map_cube(string id, int boardNum, int pinNum, CubesModel *model)
{
    //cubemapping[id] = {boardNum, pinNum};
    Group *cube = model->cubesByID[id];
    for (size_t faceindex =0; faceindex< cube->members->size(); faceindex++)
    {
        Group *face = (*cube->members)[faceindex];
        for(int stripIndex= 0;  stripIndex < face->members->size(); stripIndex++ )
        {
            Group *strip = (*face->members)[STRIP_ORD[stripIndex-1]];
            int pi=0;
            for(size_t pixelrefIndex = strip->pixels->size() - 1; ; pixelrefIndex--)
            {
                Pixel *p = (*strip->pixels)[pixelrefIndex];
                pixelmapping[p->index] = pinNum * nPointsPerPin + pi;
                pi++;
                if(pixelrefIndex == 0)
                {
                    break;
                }
            }
        }
    }
}

