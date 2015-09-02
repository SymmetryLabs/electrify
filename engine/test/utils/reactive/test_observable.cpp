#include "catch/catch.hpp"

#include "var.h"
#include "scoped_observer.h"

SCENARIO("merge()") {
    GIVEN("2 default observables and the merged result has been observed") {
        Var<int> x;
        Var<int> y;
        int calls = 0;
        int value = -1;
        {
            x.merge(y).observe([&] (int v) {
                calls++;
                value = v;
            });
        }
        WHEN("I emit from the first") {
            x.emit(10);
            THEN("I receive callbacks") {
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
        }
        WHEN("I emit from the second") {
            y.emit(11);
            THEN("I receive callbacks") {
                REQUIRE(calls == 1);
                REQUIRE(value == 11);
            }
        }
    }
    GIVEN("2 starting value observables and the merged result has been observed") {
        Var<int> x(1);
        Var<int> y(2);
        int calls = 0;
        int value = -1;
        x.merge(y).observe([&] (int v) {
            calls++;
            value = v;
        });
        THEN("I receive 2 starting callback") {
            REQUIRE(calls == 2);
        }
        THEN("The second observable gets called after the first") {
            REQUIRE(value == 2);
        }
        WHEN("I emit from the first") {
            calls = 0;
            x.emit(10);
            THEN("I receive callbacks") {
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
        }
        WHEN("I emit from the second") {
            calls = 0;
            y.emit(11);
            THEN("I receive callbacks") {
                REQUIRE(calls == 1);
                REQUIRE(value == 11);
            }
        }
        WHEN("I emit a bunch") {
            calls = 0;
            y.emit(11);
            y.emit(11);
            y.emit(11);
            x.emit(10);
            x.emit(10);
            x.emit(10);
            x.emit(10);
            y.emit(11);
            y.emit(11);
            y.emit(11);
            y.emit(11);
            y.emit(13);
            THEN("I receive callbacks") {
                REQUIRE(calls == 12);
                REQUIRE(value == 13);
            }
        }
    }
}
