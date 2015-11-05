#pragma once
#include "globals.h"

#include "pixel.h"

/**
 * Groups collect one or more pixels together
 */
class Group {

public:
    Group();
    Group(double x, double y, double z);

    Var<double> x;
    Var<double> y;
    Var<double> z;

    Var<double> rx;
    Var<double> ry;
    Var<double> rz;

    Var<string> name;
    shared_ptr<Group> parent;

    vector<shared_ptr<Group>> members;
    vector<shared_ptr<Pixel>> pixels;

    template <typename Visitor, typename... GroupType,
        typename enable_if_all<int, are_same<Group, typename std::decay<GroupType>::type...>::value>::type = 0>
    void performOnObjects(Visitor& visitor, GroupType&&... other)
    {
        visitor(x, other.x...);
        visitor(y, other.y...);
        visitor(z, other.z...);

        visitor(rx, other.rx...);
        visitor(ry, other.ry...);
        visitor(rz, other.rz...);

        visitor(name, other.name...);
    }

};
