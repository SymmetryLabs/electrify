#include "project_test_data.h"

unique_ptr<BlueprintProject> projectTestData()
{
    auto blueprint = makeBlueprint();
    auto node = blueprint->makeSubnode<TestIncrementer>("TestIncrementer");
    blueprint->wireSubnodes(*node->getOutput("output"), *blueprint->getWirableOutput("color"));

    auto model = std::make_unique<Model>();
    model->pixels.push_back(std::make_shared<Pixel>());
    return std::make_unique<BlueprintProject>(std::move(blueprint), std::move(model));
}