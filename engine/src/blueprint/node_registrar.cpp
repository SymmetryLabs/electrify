#include "node_registrar.h"

#include "node.h"
#include "node_handle.h"

#include "saw_wave.h"
#include "sin_wave.h"
#include "square_wave.h"
#include "scale_transform.h"
#include "color_doubler.h"
#include "constant_color_node.h"
#include "constant_node.h"
#include "hsv_node.h"
#include "incrementer.h"
#include "perlin_noise_node.h"
#include "pixel_x_node.h"
#include "time_node.h"
#include "translate_node.h"

#define REGISTER(nodeName) registerNode<nodeName>("nodeName");

NodeRegistrar::NodeRegistrar()
{
    REGISTER(SawWave)
    REGISTER(SinWave)
    REGISTER(SquareWave)
    REGISTER(ScaleTransform)
    REGISTER(ColorDoubler)
    REGISTER(ConstantColorNode)
    REGISTER(ConstantFloatNode)
    REGISTER(HsvNode)
    REGISTER(Incrementer)
    REGISTER(PerlinNoiseNode)
    REGISTER(PixelXNode)
    REGISTER(TimeNode)
    REGISTER(TranslateNode)
}

vector<string> NodeRegistrar::getAvailableNodeNames() const
{
    vector<string> keys;
    keys.reserve(nodeHandleFactories.size());
    for(auto kv : nodeHandleFactories) {
        keys.push_back(kv.first);
    }
    return keys;
}

size_t NodeRegistrar::getAvailableNodeCount() const
{
    return nodeHandleFactories.size();
}

shared_ptr<NodeHandle> NodeRegistrar::getNodeHandle(const string& name) const
{
    return nodeHandleFactories.at(name)();
}

void NodeRegistrar::generateNode(NodeHandle& handle) const
{
    nodeFactories.at(handle.getNodeName())(handle);
}
