#include "node_registrar.h"

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

NodeRegistrar::NodeRegistrar()
{
    registerNode<SawWave>();
    registerNode<SinWave>();
    registerNode<SquareWave>();
    registerNode<ScaleTransform>();
    registerNode<ColorDoubler>();
    registerNode<ConstantColorNode>();
    registerNode<ConstantFloatNode>();
    registerNode<HsvNode>();
    registerNode<Incrementer>();
    registerNode<PerlinNoiseNode>();
    registerNode<PixelXNode>();
    registerNode<TimeNode>();
    registerNode<TranslateNode>();
}

vector<string> NodeRegistrar::getAvailableNodeNames() const
{
    vector<string> keys;
    keys.reserve(nodeFactories.size());
    for(auto kv : nodeFactories) {
            keys.push_back(kv.first);
    }
    return keys;
}

size_t NodeRegistrar::getAvailableNodeCount() const
{
    return nodeFactories.size();
}
