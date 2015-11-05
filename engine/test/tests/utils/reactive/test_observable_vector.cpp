#include <catch/catch.hpp>

#include "observable_vector.h"

SCENARIO("using ObservableVector") {
    GIVEN("An ObservableVector<string>") {
        ObservableVector<std::string> v;
        THEN("it defaults to empty") {
            REQUIRE(v.empty());
        }
        GIVEN("I've observed adding values") {
            int calls = 0;
            std::string value;
            v.valueAdded.observe([&] (const std::pair<size_t, std::reference_wrapper<std::string>>& p) {
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

SCENARIO("copying an ObservableVector") {
    GIVEN("An ObservableVector<int>") {
        ObservableVector<int> v{2, 1};
        REQUIRE(v.size() == 2);
        WHEN("when I copy construct a new vector") {
            ObservableVector<int> v2 = v;
            THEN("the content copies") {
                REQUIRE(v2.size() == 2);
            }
            THEN("the original still has the content") {
                REQUIRE(v.size() == 2);
            }
            WHEN("I observe the original") {
                int calls = 0;
                v.sizeVar.observe([&] (size_t) {
                    calls++;
                });
                THEN("the callback is called") {
                    REQUIRE(calls == 1);
                }
            }
            WHEN("I observe the copy") {
                int calls = 0;
                v2.sizeVar.observe([&] (size_t) {
                    calls++;
                });
                THEN("the callback is called") {
                    REQUIRE(calls == 1);
                }
            }
        }
        GIVEN("a callback is registered on the size of the original") {
            int calls = 0;
            v.sizeVar.observe([&] (size_t) {
                calls++;
            });
            REQUIRE(calls == 1);
            WHEN("when I copy construct a new vector") {
                ObservableVector<int> v2 = v;
                WHEN("I change the size of the original") {
                    v.push_back(10);
                    THEN("the callback gets called") {
                        REQUIRE(calls == 2);
                    }
                }
                WHEN("I change the size of the copy") {
                    v2.push_back(11);
                    THEN("the callback gets called") {
                        REQUIRE(calls == 2);
                    }
                }
            }
        }
    }
}
