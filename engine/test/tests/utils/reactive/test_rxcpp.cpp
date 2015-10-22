#include "catch/catch.hpp"

#include <rxcpp/rx.hpp>

SCENARIO("Testing the underlying rx library") {
    GIVEN("I have an rx behavior") {
        rxcpp::subjects::behavior<int> behavior(10);

        int calls = 0;
        int value = -1;
        behavior.get_observable().subscribe([&] (int i) {
            calls++;
            value = i;
        });
        REQUIRE(calls == 1);
        REQUIRE(value == 10);

        WHEN("I move the behavior object") {
            auto behavior2 = std::move(behavior);
            THEN("calling on_next on the original does nothing") {
                behavior = rxcpp::subjects::behavior<int>{9};
                behavior.get_subscriber().on_next(11);
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
            THEN("calling on_next on the new object calls the original subscriber") {
                behavior2.get_subscriber().on_next(11);
                REQUIRE(calls == 2);
                REQUIRE(value == 11);
            }
            WHEN("I observe the new behavior object") {
                int calls2 = 0;
                int value2 = -1;
                behavior2.get_observable().subscribe([&] (int i) {
                    calls2++;
                    value2 = i;
                });
                REQUIRE(calls2 == 1);
                REQUIRE(value2 == 10);
                THEN("calls to it go to that observer") {
                    behavior2.get_subscriber().on_next(11);
                    REQUIRE(calls == 2);
                    REQUIRE(value == 11);
                    REQUIRE(calls2 == 2);
                    REQUIRE(value2 == 11);
                }
            }
        }

        GIVEN("I have the subscriber object stored") {
            auto subscriber = behavior.get_subscriber();

            GIVEN("I move the subscriber object") {
                auto subscriber2 = std::move(subscriber);

                WHEN("I call on_next on the new subscriber object") {
                    subscriber2.on_next(11);
                    THEN("The observer gets called") {
                        REQUIRE(calls == 2);
                        REQUIRE(value == 11);
                    }
                }
            }

            GIVEN("I move the behavior object") {
                auto behavior2 = std::move(behavior);

                GIVEN("I make a new subscriber object") {
                    auto subscriber2 = std::move(behavior2.get_subscriber());
                    WHEN("I call on_next on the new subscriber object") {
                        subscriber2.on_next(11);
                        THEN("The observer gets called") {
                            REQUIRE(calls == 2);
                            REQUIRE(value == 11);
                        }
                    }
                }

                WHEN("I call on_next on the stored subscriber") {
                    subscriber.on_next(11);
                    THEN("The original observer gets called") {
                        REQUIRE(calls == 2);
                        REQUIRE(value == 11);
                    }
                }

                GIVEN("I move the subscriber object") {
                    auto subscriber2 = std::move(subscriber);

                    WHEN("I call on_next on the new subscriber object") {
                        subscriber2.on_next(11);
                        THEN("The observer gets called") {
                            REQUIRE(calls == 2);
                            REQUIRE(value == 11);
                        }
                    }
                }

                GIVEN("I create the original behavior and subscriber objects") {
                    behavior = rxcpp::subjects::behavior<int>{9};
                    subscriber = behavior.get_subscriber();
                    WHEN("I call on_next on the new subscriber object") {
                        subscriber.on_next(11);
                        THEN("The original observer doesn't get called") {
                            REQUIRE(calls == 1);
                            REQUIRE(value == 10);
                        }
                    }
                }
            }
        }
        GIVEN("I have the observable object stored") {
            auto observable = behavior.get_observable();

            GIVEN("I move the observable object") {
                auto observable2 = std::move(observable);
                WHEN("I observe the new observable") {
                    int calls2 = 0;
                    int value2 = -1;
                    observable2.subscribe([&] (int i) {
                        calls2++;
                        value2 = i;
                    });
                    REQUIRE(calls2 == 1);
                    REQUIRE(value2 == 10);
                    THEN("calls to on_next both the original and new observers") {
                        behavior.get_subscriber().on_next(11);
                        REQUIRE(calls == 2);
                        REQUIRE(value == 11);
                        REQUIRE(calls2 == 2);
                        REQUIRE(value2 == 11);
                    }
                }
            }

            GIVEN("I move the behavior object") {
                auto behavior2 = std::move(behavior);

                GIVEN("I make a new observable object") {
                    auto observable2 = std::move(behavior2.get_observable());
                    WHEN("I observe the new observable") {
                        int calls2 = 0;
                        int value2 = -1;
                        observable2.subscribe([&] (int i) {
                            calls2++;
                            value2 = i;
                        });
                        REQUIRE(calls2 == 1);
                        REQUIRE(value2 == 10);
                        THEN("calls to on_next call both the original and new observers") {
                            behavior2.get_subscriber().on_next(11);
                            REQUIRE(calls == 2);
                            REQUIRE(value == 11);
                            REQUIRE(calls2 == 2);
                            REQUIRE(value2 == 11);
                        }
                    }
                }

                GIVEN("I create the original behavior and observable objects") {
                    behavior = rxcpp::subjects::behavior<int>{9};
                    observable = behavior.get_observable();
                    WHEN("I observe the new observable") {
                        int calls2 = 0;
                        int value2 = -1;
                        observable.subscribe([&] (int i) {
                            calls2++;
                            value2 = i;
                        });
                        REQUIRE(calls2 == 1);
                        REQUIRE(value2 == 9);
                        THEN("calls to on_next call the new observer") {
                            behavior.get_subscriber().on_next(11);
                            REQUIRE(calls == 1);
                            REQUIRE(value == 10);
                            REQUIRE(calls2 == 2);
                            REQUIRE(value2 == 11);
                        }
                    }
                }

                WHEN("I observe the stored observable") {
                    INFO("Causes SIGSEGV");
                    // int calls2 = 0;
                    // int value2 = -1;
                    // observable.subscribe([&] (int i) {
                    //     calls2++;
                    //     value2 = i;
                    // });
                    // REQUIRE(calls2 == 1);
                    // REQUIRE(value2 == 10);
                    // THEN("calls to on_next call the new observer") {
                    //     behavior.get_subscriber().on_next(11);
                    //     REQUIRE(calls == 1);
                    //     REQUIRE(value == 10);
                    //     REQUIRE(calls2 == 2);
                    //     REQUIRE(value2 == 11);
                    // }
                }

                GIVEN("I move the observable object") {
                    INFO("Causes SIGSEGV");
                    // auto observable2 = std::move(observable);
                    // WHEN("I observe the new observable") {
                    //     int calls2 = 0;
                    //     int value2 = -1;
                    //     observable2.subscribe([&] (int i) {
                    //         calls2++;
                    //         value2 = i;
                    //     });
                    //     REQUIRE(calls2 == 1);
                    //     REQUIRE(value2 == 10);
                    //     THEN("calls to on_next call both the original and new observers") {
                    //         behavior2.get_subscriber().on_next(11);
                    //         REQUIRE(calls == 2);
                    //         REQUIRE(value == 11);
                    //         REQUIRE(calls2 == 2);
                    //         REQUIRE(value2 == 11);
                    //     }
                    // }
                }
            }
        }
    }
}
