#include <catch/catch.hpp>

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

#include "observable_shared_ptr.h"

struct TestInternalVar {
    Var<int> v{1};
};

SCENARIO("using Observable.mapLatest()") {
    GIVEN("an observable") {
        ObservableSharedPtr<TestInternalVar> osp;
        WHEN("it is observed with mapLatest") {
            int mapCalls = 0;
            int calls = 0;
            osp.mapLatest([&] (std::shared_ptr<TestInternalVar> sp)
                    -> Var<int>& {
                mapCalls++;
                return sp->v;
            }).observe([&] (int) {
                calls++;
            });
            THEN("it receives no map callback") {
                REQUIRE(mapCalls == 0);
            }
            THEN("it receives no callback") {
                REQUIRE(calls == 0);
            }
        }
        GIVEN("an object is added") {
            osp = std::make_shared<TestInternalVar>();
            WHEN("it is observed with LATEST_PROPERTY") {
                int mapCalls = 0;
                int calls = 0;
                osp.mapLatest([&] (std::shared_ptr<TestInternalVar> sp)
                        -> Var<int>& {
                    mapCalls++;
                    return sp->v;
                }).observe([&] (int) {
                    calls++;
                });
                THEN("it receives a map callback") {
                    REQUIRE(mapCalls == 1);
                }
                THEN("it receives a callback") {
                    REQUIRE(calls == 1);
                }
            }
        }
    }
}

SCENARIO("using the LATEST_PROPERTY macro") {
    GIVEN("an observable") {
        ObservableSharedPtr<TestInternalVar> osp;
        WHEN("it is observed with LATEST_PROPERTY") {
            int calls = 0;
            LATEST_PROPERTY(osp, v).observe([&] (int) {
                calls++;
            });
            THEN("it receives no callback") {
                REQUIRE(calls == 0);
            }
        }
        GIVEN("an object is added") {
            osp = std::make_shared<TestInternalVar>();
            WHEN("it is observed with LATEST_PROPERTY") {
                int calls = 0;
                LATEST_PROPERTY(osp, v).observe([&] (int) {
                    calls++;
                });
                THEN("it receives a callback") {
                    REQUIRE(calls == 1);
                }
            }
        }
    }
}
