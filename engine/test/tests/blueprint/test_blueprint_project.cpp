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
#include "blueprint_project.h"
#include "project_serializer.h"

#include "test_blueprint_project_data.h"

SCENARIO("using blueprint project") {
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


    NodeRegistrar nodeRegistrar;
    nodeRegistrar.getAvailableNodeNames()[0];


    auto model = make_unique<Model>();
    model->pixels = {new Pixel()};

    auto blueprint = makeBlueprint();

    auto compound = blueprint->makeSubnode<CompoundNode>("CompoundNode");
    compound->registerWirableOutput<Color>("color");

    auto constantColor = compound->makeSubnode<ConstantColorNode>("ConstantColorNode");
    auto translateNode = compound->makeSubnode<TranslateNode>("TranslateNode");

    compound->wireSubnodes(*constantColor->getOutput("output"), *translateNode->getInput("ContextModifierNode"));
    compound->wireSubnodes(*translateNode->getOutput("ContextModifierNode"), *compound->getWirableOutput("color"));

    compound->wireSubnodes(*compound->getOutput("color"), *blueprint->getWirableOutput("color"));

    unique_ptr<Project> project = make_unique<BlueprintProject>(blueprint, move(model));

    WHEN("I serialize the project") {
        auto str = ProjectSerializer::serialize(project);
        THEN("It matches the expected json") {
            REQUIRE(str == serializedProject);
        }

        WHEN("I deserialize it") {
            auto deserializedProject = ProjectSerializer::deserialize(str);
            auto& deserializedBlueprintProject = dynamic_cast<BlueprintProject&>(*deserializedProject);

            auto& deserializedBlueprint = deserializedBlueprintProject.getBlueprint();
            THEN("The main blueprint node handle has the correct name") {
                REQUIRE(deserializedBlueprint.getName() == "Blueprint");
            }
        }
    }
}
