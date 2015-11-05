#include "catch/catch.hpp"

#include <rxcpp/rx.hpp>

SCENARIO("Testing the underlying rx library for initial callbacks") {
    GIVEN("I have an rx behavior") {
        rxcpp::subjects::behavior<int> behavior{10};
        auto observable = behavior.get_observable();

        WHEN("I observe it") {
            int calls = 0;
            int value = -1;
            observable.subscribe([&] (int i) {
                calls++;
                value = i;
            });
            THEN("there's an initial callback") {
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
        }

        GIVEN("a value is pushed to the behavior") {
            behavior.get_subscriber().on_next(11);

            WHEN("I observe it") {
                int calls = 0;
                int value = -1;
                observable.subscribe([&] (int i) {
                    calls++;
                    value = i;
                });
                THEN("there's an initial callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(value == 11);
                }
            }
        }
    }
}

SCENARIO("Testing rxcpp::subjects::subject with replay for initial callbacks") {
    GIVEN("I have an rx subject") {
        rxcpp::subjects::subject<int> subject;
        auto observable = subject.get_observable().replay(1).connect_forever();

        WHEN("I observe it") {
            int calls = 0;
            int value = -1;
            observable.subscribe([&] (int i) {
                calls++;
                value = i;
            });
            THEN("there is no initial callback") {
                REQUIRE(calls == 0);
                REQUIRE(value == -1);
            }
        }

        GIVEN("a value is pushed to the subject") {
            subject.get_subscriber().on_next(11);

            WHEN("I observe it") {
                int calls = 0;
                int value = -1;
                observable.subscribe([&] (int i) {
                    calls++;
                    value = i;
                });
                THEN("there's an initial callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(value == 11);
                }
            }
        }
    }
}

SCENARIO("Testing rxcpp::subjects::subject with replay with initial value for initial callbacks") {
    GIVEN("I have an rx subject") {
        rxcpp::subjects::subject<int> subject;
        auto observable = subject.get_observable().replay(1).connect_forever();
        subject.get_subscriber().on_next(10);

        WHEN("I observe it") {
            int calls = 0;
            int value = -1;
            observable.subscribe([&] (int i) {
                calls++;
                value = i;
            });
            THEN("there is no initial callback") {
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
        }

        GIVEN("a value is pushed to the subject") {
            subject.get_subscriber().on_next(11);

            WHEN("I observe it") {
                int calls = 0;
                int value = -1;
                observable.subscribe([&] (int i) {
                    calls++;
                    value = i;
                });
                THEN("there's an initial callback") {
                    REQUIRE(calls == 1);
                    REQUIRE(value == 11);
                }
            }
        }
    }
}

SCENARIO("pairing values with replaysubject") {
    GIVEN("an empty replaysubject") {
        auto rs = rxcpp::subjects::replay<int, rxcpp::identity_one_worker>(1, rxcpp::identity_current_thread());
        auto observable = rs.get_observable().zip(rxcpp::observable<>::just(0).concat(rs.get_observable().skip(1)));
        WHEN("I subscribe to the observable") {
            int calls = 0;
            observable.subscribe([&] (std::tuple<int, int>) {
                calls++;
            });
            THEN("the callback is not called") {
                REQUIRE(calls == 0);
            }
            WHEN("the subject receives a value") {
                rs.get_subscriber().on_next(10);
                THEN("the callback is called with the new value") {
                    REQUIRE(calls == 1);
                }   
            }
        }
        GIVEN("it starts with 1 value") {
            rs.get_subscriber().on_next(10);
            WHEN("I subscribe to the observable") {
                int calls = 0;
                observable.subscribe([&] (std::tuple<int, int>) {
                    calls++;
                });
                THEN("the callback is called") {
                    REQUIRE(calls == 1);
                }
            }
        }
        GIVEN("it starts with 2 values") {
            rs.get_subscriber().on_next(10);
            rs.get_subscriber().on_next(11);
            GIVEN("I subscribe to the observable") {
                int calls = 0;
                observable.subscribe([&] (std::tuple<int, int>) {
                    calls++;
                });
                THEN("the callback is called") {
                    REQUIRE(calls == 1);
                }
            }
        }
    }
}

SCENARIO("Testing the underlying rx library with moving objects and object lifetimes") {
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
