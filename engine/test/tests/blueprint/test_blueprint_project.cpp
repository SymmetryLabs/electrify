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
#include "project_file.h"
#include "file_utils.h"

#include "test_blueprint_project_data.h"

SCENARIO("using blueprint project") {
    GIVEN("I have an example project") {
        auto model = make_unique<Model>();
        model->pixels = {new Pixel()};

        auto blueprint = makeBlueprint();

        auto compound = blueprint->makeSubnode<CompoundNode>("CompoundNode");
        compound->registerWirableOutput<Color>("color");

        auto constantColor = compound->makeSubnode<ConstantColorNode>("ConstantColorNode");
        auto translateNode = compound->makeSubnode<TranslateNode>("TranslateNode");

        compound->wireSubnodes(*constantColor->getOutput("output"), *translateNode->getInput("ContextModifierNode"));
        compound->wireSubnodes(*translateNode->getOutput("ContextModifierNode"), *compound->getWirableOutput("color"));
        blueprint->wireSubnodes(*compound->getOutput("color"), *blueprint->getWirableOutput("color"));

        unique_ptr<Project> project = make_unique<BlueprintProject>(blueprint, move(model));

        WHEN("I serialize the project") {
            auto str = ProjectSerializer::serialize(project);
            THEN("It matches the expected json") {
                CHECKED_ELSE(str == serializedProject) {
                    std::cout << str << std::endl;
                }
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
        WHEN("I write to file") {
            ProjectFile pf("test.symproj");
            pf.saveToFile(project);
            THEN("The file exists") {
                REQUIRE(file_exists("test.symproj"));
            }
            THEN("The file is correct") {
            }
        }
    }
    WHEN("I load from file") {
        ProjectFile pf("default.symproj");
        auto project = pf.loadFromFile();
        THEN("The project loads") {
            REQUIRE(project);
        }
    }
}
