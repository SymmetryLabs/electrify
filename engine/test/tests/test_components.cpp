#include <catch/catch.hpp>

// #include "globals.h"
// #include "constant_color_node.h"
// #include "frame_context.h"
// #include "color.h"

// SCENARIO( "Create a Constant Color node", "[node]" ) {

//   GIVEN( "A Constant Color Node" ) {
//     ConstantColorNode c;

//     WHEN("We inspect its name") {
      
//       THEN("We get a value") {
//         REQUIRE(c.nodeName() != "");
//       }
//     }
//     GIVEN("A Frame") {
//       FrameContext frame {nanoseconds(100)};

//       WHEN("We caculate its color output") {
//         Color color = c.getOutput<Color>("output")->calculate(frame);

//         THEN("We get the default color back") {
//           REQUIRE(color.asRGBA() == 0xFF0000FF);
//         }
//       }
//       WHEN("We can change the node color and get the correct") {
//         c.color.fromRGBA(0x00FF00FF);
//         Color color = c.getOutput<Color>("output")->calculate(frame);

//         THEN("We get the right color back") {
//           REQUIRE(color.asRGBA() == 0x00FF00FF);
//         }
//       }
//     }
//   }
// }