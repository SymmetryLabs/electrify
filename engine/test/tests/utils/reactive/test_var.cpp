#include <catch/catch.hpp>

#include "var.h"

SCENARIO("using Var<int>") {

    WHEN("instatiated") {
        Var<int> v;
        THEN("defaults to 0") {
            REQUIRE(v.getValue() == 0);
        }
    }

    WHEN("instantiated with 10") {
        Var<int> v(10);
        THEN("it has 10") {
            REQUIRE(v.getValue() == 10);
        }
    }

    GIVEN("I have a variable of the inner type") {
        int i = 5;
        WHEN("I copy construct a Var from it") {
            Var<int> v = i;
            THEN("It converts implicitly") {
                REQUIRE(v.getValue() == 5);
            }
        }
    }

    GIVEN("a default Var") {
        Var<int> v;

        WHEN("I set assign it to a variable of the inner type") {
            int i = v;
            THEN("It converts implicitly") {
                REQUIRE(i == 0);
            }
        }

        GIVEN("I have a variable of the inner type") {
            int i = 4;
            WHEN("I copy assign it to the Var") {
                v = i;
                THEN("It converts implicitly") {
                    REQUIRE(v.getValue() == 4);
                }
            }
        }

        WHEN("I emit a value") {
            v.emit(9);
            THEN("it contains the value") {
                REQUIRE(v.getValue() == 9);
            }
        }

        GIVEN("I subscribe to it") {
            int calls = 0;
            int value = -1;
            v.observe([&] (int i) {
                calls++;
                value = i;
            });
            THEN("It should not call without emitting a value") {
                REQUIRE(calls == 0);
                REQUIRE(value == -1);
            }
            WHEN("I emit a value") {
                v.emit(5);
                THEN("the subscriber gets called only once") {
                    REQUIRE(calls == 1);
                }
                THEN("the subscriber receives the value") {
                    REQUIRE(value == 5);
                }
            }
        }
    }

    GIVEN("") {
        int i = 0;
        Var<int> master;
        Var<int> slave;
        {
            master.observe([&] (int j) {
                slave.emit(j);
                i++;
            });
        }
        master.emit(2);
        REQUIRE(master.getValue() == 2);
        REQUIRE(i == 1);
    }

    GIVEN("a Var with a starting value") {
        Var<int> v(10);

        WHEN("I emit a value") {
            v.emit(9);
            THEN("it contains the value") {
                REQUIRE(v.getValue() == 9);
            }
        }

        GIVEN("I subscribe to it") {
            int calls = 0;
            int value = -1;
            v.observe([&] (int i) {
                calls++;
                value = i;
            });
            THEN("It should callback with the starting value") {
                REQUIRE(calls == 1);
                REQUIRE(value == 10);
            }
            WHEN("I emit a value") {
                v.emit(5);
                THEN("the subscriber gets called twice") {
                    REQUIRE(calls == 2);
                }
                THEN("the subscriber receives the value") {
                    REQUIRE(value == 5);
                }
            }
        }
        GIVEN("I emitted several values") {
            v.emit(1);
            v.emit(2);
            v.emit(3);
            WHEN("I subscribe to it") {
                int calls = 0;
                int value = -1;
                v.observe([&] (int i) {
                    calls++;
                    value = i;
                });
                THEN("it should only be called once") {
                    REQUIRE(calls == 1);
                }
                THEN("it should have the latest value") {
                    REQUIRE(value == 3);
                }
                WHEN("I emit again") {
                    v.emit(5);
                    THEN("it should be called twice") {
                        REQUIRE(calls == 2);
                    }
                    THEN("it should have the latest value") {
                        REQUIRE(value == 5);
                    }
                }
            }
        }
    }
    GIVEN("I have a Var and subscribe to it") {
        Var<int> v;
        int calls = 0;
        v.observe([&] (int) {
            calls++;
        });

        GIVEN("I move construct it") {
            Var<int> v2(std::move(v));
            THEN("It moves the observer") {
                v2.emit(5);
                REQUIRE(calls == 1);
            }
            GIVEN("I subscribe to the second") {
                INFO("Pending (causes SIGSEGV)");
                // int calls2 = 0;
                // v2.observe([&] (int) {
                //     calls2++;
                // });
                // WHEN("I call the original") {
                //     v.emit(5);
                //     THEN("I don't receive callbacks") {
                //         REQUIRE(calls == 0);
                //         REQUIRE(calls2 == 0);
                //     }
                // }
                // WHEN("I call the second") {
                //     v2.emit(5);
                //     THEN("I receive callbacks") {
                //         REQUIRE(calls == 1);
                //         REQUIRE(calls2 == 1);
                //     }
                // }
            }
        }
        GIVEN("I move assign it") {
            Var<int> v2;
            v2 = std::move(v);
            THEN("It moves the observer") {
                v2.emit(5);
                REQUIRE(calls == 1);
            }
            GIVEN("I subscribe to the second") {
                INFO("Pending (causes SIGSEGV)");
                // int calls2 = 0;
                // v2.observe([&] (int) {
                //     calls2++;
                // });
                // WHEN("I call the original") {
                //     v.emit(5);
                //     THEN("I don't receive callbacks") {
                //         REQUIRE(calls == 0);
                //         REQUIRE(calls2 == 0);
                //     }
                // }
                // WHEN("I call the second") {
                //     v2.emit(5);
                //     THEN("I receive callbacks") {
                //         REQUIRE(calls == 1);
                //         REQUIRE(calls2 == 1);
                //     }
                // }
            }
        }
        GIVEN("I copy construct it") {
            Var<int> v2(v);
            THEN("It moves the observer") {
                v2.emit(5);
                REQUIRE(calls == 1);
            }
            GIVEN("I subscribe to the second") {
                int calls2 = 0;
                v2.observe([&] (int) {
                    calls2++;
                });
                WHEN("I call the original") {
                    v.emit(5);
                    THEN("I get callbacks for both") {
                        REQUIRE(calls == 1);
                        REQUIRE(calls2 == 1);
                    }
                }
                WHEN("I call the second") {
                    v2.emit(5);
                    THEN("I get callbacks for both") {
                        REQUIRE(calls == 1);
                        REQUIRE(calls2 == 1);
                    }
                }
            }
        }
        GIVEN("I copy assign it") {
            Var<int> v2;
            v2 = v;
            THEN("It moves the observer") {
                v2.emit(5);
                REQUIRE(calls == 1);
            }
            GIVEN("I subscribe to the second") {
                int calls2 = 0;
                v2.observe([&] (int) {
                    calls2++;
                });
                WHEN("I call the original") {
                    v.emit(5);
                    THEN("I get callbacks for both") {
                        REQUIRE(calls == 1);
                        REQUIRE(calls2 == 1);
                    }
                }
                WHEN("I call the second") {
                    v2.emit(5);
                    THEN("I get callbacks for both") {
                        REQUIRE(calls == 1);
                        REQUIRE(calls2 == 1);
                    }
                }
                WHEN("The original goes out of scope") {
                    Var<int> v11;
                    int calls10 = 0;
                    int calls11a = 0;
                    {
                        Var<int> v10;
                        v10.observe([&] (int) {
                            calls10++;
                        });
                        v11 = v10;
                        v11.observe([&] (int) {
                            calls11a++;
                        });
                    }
                    int calls11b = 0;
                    v11.observe([&] (int) {
                        calls11b++;
                    });
                    THEN("I still get callbacks") {
                        v11.emit(5);
                        REQUIRE(calls10 == 1);
                        REQUIRE(calls11a == 1);
                        REQUIRE(calls11b == 1);
                    }
                }
                WHEN("The second goes out of scope") {
                    Var<int> v10;
                    int calls10a = 0;
                    v10.observe([&] (int) {
                        calls10a++;
                    });
                    int calls11 = 0;
                    {
                        Var<int> v11;
                        v11 = v10;
                        v11.observe([&] (int) {
                            calls11++;
                        });
                    }
                    int calls10b = 0;
                    v10.observe([&] (int) {
                        calls10b++;
                    });
                    THEN("I still get callbacks for both") {
                        v10.emit(5);
                        REQUIRE(calls10a == 1);
                        REQUIRE(calls10b == 1);
                        REQUIRE(calls11 == 1);
                        
                    }
                }
            }
        }
    }
}

SCENARIO("Using Var<string>") {
    WHEN("I construct a default Var<string>") {
        Var<std::string> v;
        THEN("It has a value of an empty string") {
            REQUIRE(v.getValue() == "");
        }
    }
    WHEN("I construct a Var with a value") {
        Var<std::string> v("value");
        THEN("It has that value") {
            REQUIRE(v.getValue() == "value");
        }
    }
    WHEN("I construct the var with a moved value") {
        std::string s = "value";
        Var<std::string> v(std::move(s));
        THEN("the var has the value but the original source doesn't") {
            REQUIRE(v.getValue() == "value");
            REQUIRE(s == "");
        }
    }
}
