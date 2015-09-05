#include <catch/catch.hpp>

#include "observable_vector.h"

SCENARIO("using ObservableVector") {
    GIVEN("An ObservableVector<string>") {
        ObservableVector<std::string> v;
        REQUIRE(v.empty());
        GIVEN("I've observed adding values") {
            int calls = 0;
            std::string value;
            v.valueAdded.observe([&] (const std::pair<size_t, std::reference_wrapper<const std::string>>& p) {
                calls++;
                value = p.second.get();
            });
            WHEN("I add a value") {
                v.push_back("test");
                THEN("I receive a callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(value == "test");
                    REQUIRE(v.size() == 1);
                }
            }
        }
        GIVEN("I've observed removing values") {
            v.push_back("first");
            REQUIRE(v.size() == 1);
            int calls = 0;
            v.valueRemoved.observe([&] (size_t) {
                calls++;
            });
            WHEN("I remove a value using pop_back()") {
                v.pop_back();
                THEN("I receive a callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(v.empty());
                }
            }
        }
    }
}
