#include <catch/catch.hpp>

#include "observable_map.h"

SCENARIO("using ObservableMap") {
    GIVEN("An ObservableMap<string, int>") {
        ObservableMap<std::string, int> m;
        REQUIRE(m.empty());
        GIVEN("I've observed adding values") {
            int calls = 0;
            std::string key;
            int value;
            m.valueAdded.observe([&] (const std::pair<const std::string, int>& p) {
                calls++;
                key = p.first;
                value = p.second;
            });
            WHEN("I add a value") {
                m.insert(std::make_pair("test", 10));
                THEN("I receive a callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(key == "test");
                    REQUIRE(value == 10);
                    REQUIRE(m.size() == 1);
                }
            }
        }
        GIVEN("I've observed removing values") {
            m.insert(std::make_pair("first", 2));
            REQUIRE(m.size() == 1);
            int calls = 0;
            std::string key;
            m.valueRemoved.observe([&] (const std::string& k) {
                calls++;
                key = k;
            });
            WHEN("I remove a value using erase()") {
                m.erase(m.begin());
                THEN("I receive a callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(key == "first");
                    REQUIRE(m.empty());
                }
            }
        }
    }
}

#include "data_bridge.h"

SCENARIO("proxying ObservableMaps") {

    GIVEN("2 ObservableMaps") {
        ObservableMap<std::string, int> m1;
        ObservableMap<std::string, int> m2;
        GIVEN("they are in master/slave configuration") {
            DataBridge db;
            DataProxy& dp = db.getMasterProxy();
            m1.makeProxySlave(m2, dp);
            WHEN("I add to the master") {
                m1.insert(std::make_pair("test", 10));
                db.flushAll();
                REQUIRE(m1.size() == 1);
                THEN("It adds to the slave") {
                    REQUIRE(m2.size() == 1);
                    REQUIRE(m2.at("test") == 10);
                    REQUIRE(m2.count("test") == 1);
                }
            }
        }
    }

    GIVEN("2 ObservableMaps with starting values in master") {
        ObservableMap<std::string, int> m1;
        m1.insert(std::make_pair("first", 10));
        REQUIRE(m1.size() == 1);
        ObservableMap<std::string, int> m2;
        WHEN("I set up the proxy") {
            DataBridge db;
            DataProxy& dp = db.getMasterProxy();
            m1.makeProxySlave(m2, dp);
            THEN("The slave gets the starting values") {
                REQUIRE(m2.size() == 1);
                REQUIRE(m2.count("first"));
                REQUIRE(m2.at("first") == 10);
                REQUIRE(m2.count("second") == 0);
                REQUIRE(m2.size() == 1);
            }

            WHEN("I add to the master") {
                m1.insert(std::make_pair("second", 11));
                db.flushAll();
                REQUIRE(m2.size() == 2);
                THEN("It adds to the slave") {
                    REQUIRE(m2.size() == 2);
                    REQUIRE(m2.at("first") == 10);
                    REQUIRE(m2.at("second") == 11);
                    REQUIRE(m2.count("first") == 1);
                    REQUIRE(m2.count("second") == 1);
                    REQUIRE(m2.count("third") == 0);
                    REQUIRE(m2.size() == 2);
                }
            }

            WHEN("I remove from the master") {
                m1.erase(m1.begin());
                db.flushAll();
                REQUIRE(m2.empty());
                THEN("It removes from the slave") {
                    REQUIRE(m2.empty());
                    REQUIRE(m2.count("first") == 0);
                    REQUIRE(m2.count("second") == 0);
                    REQUIRE(m2.count("third") == 0);
                    REQUIRE(m2.empty());
                }
            }
        }
    }

}
