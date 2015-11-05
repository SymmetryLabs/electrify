#include "catch/catch.hpp"

#include "observable_shared_ptr.h"

SCENARIO("Using ObservableSharedPtr") {
    GIVEN("I have an ObservableSharedPtr") {
        auto i = ObservableSharedPtr<int>{new int(10)};
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
            i.previous().observe([&] (std::shared_ptr<int> removed) {
                removedCount++;
                removedValue = *removed;
            });
            i.observe([&] (std::shared_ptr<int> added) {
                addedCount++;
                addedValue = *added;
            });
            THEN("It sends a callback immediately") {
                REQUIRE(addedCount == 1);
            }
            WHEN("I reset to a new value") {
                i.reset(new int(5));
                THEN("The observers gets called") {
                    REQUIRE(removedCount == 1);
                    REQUIRE(addedCount == 2);
                    REQUIRE(removedValue == 10);
                    REQUIRE(addedValue == 5);
                }
            }
        }
    }
}

struct Test {
};

SCENARIO("Using ObservableSharedPtr with a custom type") {
    GIVEN("an empty ObservableSharedPtr") {
        ObservableSharedPtr<Test> osp;
        GIVEN("I observe it") {
            int calls = 0;
            osp.observe([&] (const std::shared_ptr<Test>&) {
                calls++;
            });
            THEN("it starts with no callbacks") {
                REQUIRE(calls == 0);
            }
            WHEN("I set the ObservableSharedPtr to an object") {
                osp = std::make_shared<Test>();
                THEN("the ObservableSharedPtr has an object") {
                    REQUIRE(osp);
                }
                THEN("there is a callback") {
                    REQUIRE(calls == 1);
                }
            }
        }
        WHEN("I set the ObservableSharedPtr to an object") {
            osp = std::make_shared<Test>();
            WHEN("I observe it") {
                int calls = 0;
                osp.observe([&] (const std::shared_ptr<Test>&) {
                    calls++;
                });
                THEN("it sends a callback immediately") {
                    REQUIRE(calls == 1);
                }
            }
        }
    }

}
