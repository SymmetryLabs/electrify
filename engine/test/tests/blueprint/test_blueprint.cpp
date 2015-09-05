#include <catch/catch.hpp>

#include "color.h"
#include "constant_color_node.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"
#include "engine.h"
#include "loader.h"
#include "compound_node.h"
#include "translate_node.h"
#include "blueprint.h"
#include "node_registrar.h"

SCENARIO("using blueprint") {
    FrameContext frame {nanoseconds(100)};

    ConstantColorNode c;
    REQUIRE(c.calculate(frame) == Color(0xff0000ff));

    ColorDoubler colorDoubler;
    c.getOutput("output")->wireOutput(*colorDoubler.getInput("color"));
    REQUIRE(colorDoubler.calculate(frame) == Color(0xfe0001fe));

    SquareWave sq;
    REQUIRE(sq.calculate(frame) == 0);

    Incrementer incr;
    colorDoubler.getOutput("output")->wireOutput(*incr.getInput("color"));
    REQUIRE(incr.calculate(frame) == Color(0xfe0001fe));

    incr.update(frame);
    REQUIRE(incr.calculate(frame) == Color(0xfe0002fe));

    incr.update(frame);
    REQUIRE(incr.calculate(frame) == Color(0xfe0003fe));


    NodeRegistrar nodeRegistrar;
    nodeRegistrar.getAvailableNodeNames()[0];


    auto blueprint = make_shared<Blueprint>();
    auto model = make_unique<Model>();
    model->pixels = {new Pixel()};

    auto compound = blueprint->makeSubnode<CompoundNode>();
    compound->registerWirableOutput<Color>("color");

    auto constantColor = compound->makeSubnode<ConstantColorNode>();
    auto translateNode = compound->makeSubnode<TranslateNode>();

    compound->wireSubnodes(*constantColor->getOutput("output"), *translateNode->getInput("Translate"));
    compound->wireSubnodes(*translateNode->getOutput("Translate"), *compound->getWirableOutput("color"));

    compound->wireSubnodes(*compound->getOutput("color"), *blueprint->getWirableOutput("color"));

    Engine engine(blueprint, move(model));
    engine.startAndWait();
}
