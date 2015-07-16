#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"
#include "component.h"

SCENARIO( "Create and Wire a component", "[component]" ) {

  GIVEN( "A Component" ) {
    Component *c= new Component();
    REQUIRE(c)
  }
}
