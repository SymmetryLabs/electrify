#include "catch/catch.hpp"

#include "globals.h"
#include "output.h"
#include "blueprint.h"
#include "constant_color_component.h"
#include "incrementer.h"

SCENARIO( "wiring a blueprint", "[blueprint]" ) {
  GIVEN("A Blueprint a frame, a model and an output") {
    auto blueprint = make_unique<Blueprint>();
    FrameContext frame {nanoseconds(100)};
    Output output;
    GIVEN("A mocked model and color buffer") {

      Model model;
      model.pixels = {
        new Pixel(),
        new Pixel(),
        new Pixel(),
        new Pixel(),
      };
      for (auto p : model.pixels) {
        output.colorBuffer.push_back(Color(0xFFFFFFFF));
      }
      blueprint->initRenderable(model);
      

      GIVEN("A CompoundComponent with A registered color output ")
      {
        auto compound = blueprint->makeSubcomponent<CompoundComponent>();
        compound->registerWirableOutput<Color>("color");

        GIVEN("Two subcomponents (constant color, incrementer)")
        {
          auto constantColor = compound->makeSubcomponent<ConstantColorComponent>();
          auto incrementer = compound->makeSubcomponent<Incrementer>();
          GIVEN("The components are wired up to the blueprint")
          {
            compound->wireSubcomponents(*constantColor, "output", *incrementer, "color");
            compound->wireOutput("color", *incrementer, "output");
            blueprint->wireOutput("color", *compound, "color");
            WHEN("The blueprint is updated")
            {
              blueprint->update(frame);
              THEN("no crash")
              {
                REQUIRE(1);
              }
            }
            WHEN("The blueprint is rendered to the output's color buffer")
            {
              blueprint->renderRenderable(frame, output.colorBuffer);
              THEN("no crash")
              {
                REQUIRE(1);
              }
            }
          }
        }  
      }      
    }
  }
}