#include "scalar_transform.h"

ScalarTransform::ScalarTransform(NodeHandle& nodeHandle)
: BasicNode<float>(nodeHandle)
{
    nodeHandle.registerInput("input", &input);
}
