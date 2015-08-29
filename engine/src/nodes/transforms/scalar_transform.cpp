#include "scalar_transform.h"

ScalarTransform::ScalarTransform(const string& name)
: BasicNode<float>(name)
{
    registerInput("input", &input);
}
