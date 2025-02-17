#include <catch/catch.hpp>

#include "color.h"
#include "constant_color_node.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "model.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"
#include "engine.h"
#include "loader.h"
#include "compound_node.h"
#include "translate_node.h"
#include "blueprint.h"
#include "node_registrar.h"
#include "blueprint_project.h"

SCENARIO("using blueprint") {
    FrameContext frame {nanoseconds(100)};

    auto colorNodeHandle = makeNodeHandle<ConstantColorNode>("ConstantColorNode");
    auto& colorNode = colorNodeHandle->getNode<ConstantColorNode>();
    REQUIRE(colorNode.calculate(frame) == Color(0xff0000ff));

    auto colorDoublerHandle = makeNodeHandle<ColorDoubler>("ColorDoubler");
    auto& colorDoubler = colorDoublerHandle->getNode<ColorDoubler>();
    colorNodeHandle->getOutput("output")->wireOutput(*colorDoublerHandle->getInput("color"));
    REQUIRE(colorDoubler.calculate(frame) == Color(0xfe0001fe));

    auto squareWaveHandle = makeNodeHandle<SquareWave>("SquareWave");
    auto& squareWave = squareWaveHandle->getNode<SquareWave>();
    REQUIRE(squareWave.calculate(frame) == 0);

    auto incrementerHandle = makeNodeHandle<Incrementer>("Incrementer");
    auto& incrementer = incrementerHandle->getNode<Incrementer>();
    colorDoublerHandle->getOutput("output")->wireOutput(*incrementerHandle->getInput("color"));
    REQUIRE(incrementer.calculate(frame) == Color(0xfe0001fe));

    incrementer.update(frame);
    REQUIRE(incrementer.calculate(frame) == Color(0xfe0002fe));

    incrementer.update(frame);
    REQUIRE(incrementer.calculate(frame) == Color(0xfe0003fe));


    NodeRegistrar& nodeRegistrar = NodeRegistrar::getInstance();
    nodeRegistrar.getAvailableNodeNames()[0];
}

SCENARIO("typical engine startup") {
    auto model = make_unique<Model>();
    model->pixels = {make_shared<Pixel>()};

    auto blueprint = makeBlueprint();

    auto compound = blueprint->makeSubnode<CompoundNode>("CompoundNode");
    compound->registerWirableOutput("color", compound->getNode<CompoundNode>().generateWirableOutput<Color>());

    auto constantColor = compound->makeSubnode<ConstantColorNode>("ConstantColorNode");
    auto translateNode = compound->makeSubnode<TranslateNode>("TranslateNode");

    compound->wireSubnodes(*constantColor->getOutput("output"), *translateNode->getInput("ContextModifierNode"));
    compound->wireSubnodes(*translateNode->getOutput("ContextModifierNode"), *compound->getWirableOutput("color"));

    blueprint->wireSubnodes(*compound->getOutput("color"), *blueprint->getWirableOutput("color"));

    auto project = make_unique<BlueprintProject>(blueprint, move(model));

    GIVEN("an Engine") {
        Engine engine;
        engine.loadProject(move(project));
        WHEN("I start it") {
            THEN("it works") {
                engine.startAndWait();
            }
        }
    }
}
