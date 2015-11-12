#include <catch/catch.hpp>

// #include "globals.h"
// #include "output.h"
// #include "blueprint.h"
// #include "constant_color_node.h"
// #include "incrementer.h"

// SCENARIO( "wiring a blueprint", "[node],[blueprint]" ) {
//   GIVEN("A Blueprint, a frame and an output") {
//     auto blueprint = make_unique<Blueprint>();
//     FrameContext frame {nanoseconds(100)};
//     Output output;
//     GIVEN("A mocked model and color buffer") {

//       Model model;
//       model.pixels = {
//         new Pixel(),
//         new Pixel(),
//         new Pixel(),
//         new Pixel(),
//       };
//       for (auto p : model.pixels) {
//         output.colorBuffer.push_back(Color(0xFFFFFFFF));
//       }
//       blueprint->initRenderable(model);


//       GIVEN("A CompoundNode with A registered color output ") {
//         auto compound = blueprint->makeSubnode<CompoundNode>();
//         compound->registerWirableOutput<Color>("color");

//         GIVEN("Two subnodes (constant color, incrementer)") {
//           auto constantColor = compound->makeSubnode<ConstantColorNode>();
//           auto incrementer = compound->makeSubnode<Incrementer>();

//           GIVEN("The nodes are wired up to the blueprint") {
//             compound->wireSubnodes(*constantColor, "output", *incrementer, "color");
//             compound->wireOutput("color", *incrementer, "output");
//             blueprint->wireOutput("color", *compound, "color");

//             WHEN("The blueprint is updated") {
//               blueprint->update(frame);
//               THEN("no crash") {
//                 REQUIRE(1); //TODO fill in more details
//               }
//             }

//             WHEN("The blueprint is rendered to the output's color buffer") {
//               blueprint->renderRenderable(frame, output.colorBuffer);
//               THEN("no crash") {
//                 REQUIRE(1); //TODO fill in more details
//               }
//             }
//           }
//         }
//       }
//     }
//   }
// }