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
    registerNode<SawWave>("SawWave");
    registerNode<SinWave>("SinWave");
    registerNode<SquareWave>("SquareWave");
    registerNode<ScaleTransform>("ScaleTransform");
    registerNode<ColorDoubler>("ColorDoubler");
    registerNode<ConstantColorNode>("ConstantColorNode");
    registerNode<ConstantFloatNode>("ConstantFloatNode");
    registerNode<HsvNode>("HsvNode");
    registerNode<Incrementer>("Incrementer");
    registerNode<PerlinNoiseNode>("PerlinNoiseNode");
    registerNode<PixelXNode>("PixelXNode");
    registerNode<TimeNode>("TimeNode");
    registerNode<TranslateNode>("TranslateNode");
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
