#include "catch/catch.hpp"

#include "observable_shared_ptr.h"

SCENARIO("Using ObservableSharedPtr") {
    GIVEN("I have an ObservableSharedPtr") {
        auto i = ObservableSharedPtr<int>(new int(10));
        WHEN("I dereference it") {
            THEN("It has the value") {
                REQUIRE(*i == 10);
            }
        }
        GIVEN("I have observed it") {
            int removedCount = 0;
            int addedCount = 0;
            int removedValue = 0;
            int addedValue = 0;
            i.willRemoveValue.observe([&] (int* removed) {
                removedCount++;
                removedValue = *removed;
            });
            i.didAddValue.observe([&] (int* added) {
                addedCount++;
                addedValue = *added;
            });
            WHEN("I reset to a new value") {
                i.reset(new int(5));
                THEN("The observers gets called") {
                    REQUIRE(removedCount == 1);
                    REQUIRE(addedCount == 1);
                    REQUIRE(removedValue == 10);
                    REQUIRE(addedValue == 5);
                }
            }
        }
    }
}
