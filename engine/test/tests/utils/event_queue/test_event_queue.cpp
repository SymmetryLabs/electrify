#include <catch/catch.hpp>

#include "event_queue.h"

SCENARIO("Using EventQueue") {
    GIVEN("I have an event queue") {
        EventQueue eq;
        WHEN("I queue an event") {
            int i = 0;
            eq.queueEvent([&] {
                i++;
            });
            THEN("It doesn't execute right away") {
                REQUIRE(i == 0);
            }
            WHEN("I flush the queue") {
                eq.flush();
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I flush the queue twice") {
                eq.flush();
                eq.flush();
                THEN("It only executes once") {
                    REQUIRE(i == 1);
                }
            }
        }
    }
}