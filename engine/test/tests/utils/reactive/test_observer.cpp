#include <catch/catch.hpp>

#include "var.h"
#include "observer.h"

SCENARIO("using observer") {

    GIVEN("I have a var") {
        Var<int> v;
        Var<int> v2;
        WHEN("I subscribe to it") {
            THEN("I can make an observer from it") {
                Observer o(v.observe([] (int) {
                }));
            }
        }
        GIVEN("I have an observer that is subscribed to it") {
            int calls = 0;
            Observer o(v.observe([&] (int) {
                calls++;
            }));
            WHEN("I don't unsubscribe") {
                THEN("I receive callbacks") {
                    v.emit(1);
                    REQUIRE(calls == 1);
                }
            }
            WHEN("I unsubscribe") {
                o.unsubscribe();
                THEN("I don't receive callbacks") {
                    v.emit(1);
                    REQUIRE(calls == 0);
                }
            }
            GIVEN("I move construct using the observer") {
                Observer o2(std::move(o));
                WHEN("I unsubscribe from the first one") {
                    o.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
                WHEN("I unsubscribe from the second one") {
                    o2.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
            GIVEN("I move assing the observer") {
                Observer o2(v2.observe([] (int) {
                }));
                o2 = std::move(o);
                WHEN("I unsubscribe from the first one") {
                    o.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
                WHEN("I unsubscribe from the second one") {
                    o2.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
            GIVEN("I copy assign using the observer") {
                Observer o2(v2.observe([] (int) {
                }));
                o2 = o;
                WHEN("I unsubscribe from the first one") {
                    o.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
                WHEN("I unsubscribe from the second one") {
                    o2.unsubscribe();
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
        }
        GIVEN("I have an observer that is subscribed to it") {
            int calls = 0;
            {
                Observer o(v.observe([&] (int) {
                    calls++;
                }));
            }
            WHEN("I go out of scope of the observer") {
                THEN("I still receive callbacks") {
                    v.emit(1);
                    REQUIRE(calls == 1);
                }
            }
        }
    }

}
