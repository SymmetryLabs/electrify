#include <catch/catch.hpp>

#include "data_proxy.h"
#include "event_queue.h"

SCENARIO("Using a DataProxy") {
    GIVEN("I have a DataProxy that doesn't point to anything") {
        DataProxy dp;
        WHEN("I send an event") {
            int i = 0;
            dp.sendEvent([&] () {
                i++;
            });
            THEN("It calls it immediately") {
                REQUIRE(i == 1);
            }
        }
    }
    GIVEN("I have a DataProxy with an event queue") {
        auto eq = std::make_shared<EventQueue>();
        DataProxy dp(eq);
        WHEN("I send an event") {
            int i = 0;
            dp.sendEvent([&] () {
                i++;
            });
            THEN("It doesn't call it immediately") {
                REQUIRE(i == 0);
            }
            WHEN("When I empty the queue") {
                eq->flush();
                THEN("It calls it") {
                    REQUIRE(i == 1);
                }
            }
        }
    }
}
