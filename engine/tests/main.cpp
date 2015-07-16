#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"
#include "basic_component.h"

TEST_CASE( "Can create a component", "[Component]" ) {

   Component *c= new Component();
}
