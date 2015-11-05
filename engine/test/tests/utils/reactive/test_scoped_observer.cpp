#include <catch/catch.hpp>

#include "var.h"
#include "observer.h"
#include "scoped_observer.h"

SCENARIO("Using ScopedObserver") {

    GIVEN("I have an observer") {
        Var<int> v;
        int calls = 0;
        Observer o(v.observe([&] (int) {
            calls++;
        }));

        THEN("I can make a scoped observer from it") {
            ScopedObserver so(std::move(o));
        }

        GIVEN("I have a scoped observer created from it") {
            WHEN("It doesn't go out of scope") {
                ScopedObserver so(std::move(o));
                THEN("I receive callbacks") {
                    v.emit(1);
                    REQUIRE(calls == 1);
                }
            }
            WHEN("It goes out of scope") {
                {
                    ScopedObserver so(std::move(o));
                }
                THEN("I don't receive callbacks") {
                    v.emit(1);
                    REQUIRE(calls == 0);
                }
            }
            GIVEN("I move construct it") {
                WHEN("It doesn't go out of scope") {
                    ScopedObserver so(std::move(o));
                    ScopedObserver so2(std::move(so));
                    THEN("I still receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 1);
                    }
                }
                WHEN("It goes out of scope") {
                    {
                        ScopedObserver so(std::move(o));
                        ScopedObserver so2(std::move(so));
                    }
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
            GIVEN("I copy construct using the observer") {
                WHEN("It doesn't go out of scope") {
                    ScopedObserver so(std::move(o));
                    ScopedObserver so2(so);
                    THEN("I still receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 1);
                    }
                }
                WHEN("It goes out of scope") {
                    {
                        ScopedObserver so(std::move(o));
                        ScopedObserver so2(so);
                    }
                    THEN("I don't receive callbacks") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
        }

        GIVEN("I have a second observer") {
            Var<int> v2;
            Observer o2(v2.observe([] (int) {
            }));
            GIVEN("I have a scoped observer created from it") {
                GIVEN("I move assign it") {
                    WHEN("They both go out of scope") {

                        {
                            ScopedObserver so(std::move(o));
                            ScopedObserver so2(std::move(o2));
                            so2 = std::move(so);
                        }
                        THEN("I don't receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 0);
                        }
                    }
                    WHEN("They first one goes out of scope") {
                        ScopedObserver so2(std::move(o2));
                        {
                            ScopedObserver so(std::move(o));
                            so2 = std::move(so);
                        }
                        THEN("I still receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 1);
                        }
                    }
                    WHEN("They second one goes out of scope") {
                        ScopedObserver so(std::move(o));
                        {
                            ScopedObserver so2(std::move(o2));
                            so2 = std::move(so);
                        }
                        THEN("I don't receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 0);
                        }
                    }
                    WHEN("Neither goes out of scope") {
                        ScopedObserver so(std::move(o));
                        ScopedObserver so2(std::move(o2));
                        so2 = std::move(so);
                        THEN("I still receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 1);
                        }
                    }
                }
                GIVEN("I copy assign it") {
                    WHEN("They both go out of scope") {

                        {
                            ScopedObserver so(std::move(o));
                            ScopedObserver so2(std::move(o2));
                            so2 = so;
                        }
                        THEN("I don't receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 0);
                        }
                    }
                    WHEN("They first one goes out of scope") {
                        ScopedObserver so2(std::move(o2));
                        {
                            ScopedObserver so(std::move(o));
                            so2 = so;
                        }
                        THEN("I still receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 1);
                        }
                    }
                    WHEN("They second one goes out of scope") {
                        ScopedObserver so(std::move(o));
                        {
                            ScopedObserver so2(std::move(o2));
                            so2 = so;
                        }
                        THEN("I still receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 1);
                        }
                    }
                    WHEN("Neither goes out of scope") {
                        ScopedObserver so(std::move(o));
                        ScopedObserver so2(std::move(o2));
                        so2 = so;
                        THEN("I still receive callbacks") {
                            v.emit(1);
                            REQUIRE(calls == 1);
                        }
                    }
                }
            }
        }

        GIVEN("I have 2 ScopedObservers created from it") {
            ScopedObserver so(std::move(o));
            ScopedObserver so2(so);
            WHEN("I explicitly release one") {
                so.release();
                THEN("I don't receive the callback") {
                    v.emit(1);
                    REQUIRE(calls == 0);
                }
            }
            WHEN("I explicitly release both") {
                so.release();
                so2.release();
                THEN("I don't receive the callback") {
                    v.emit(1);
                    REQUIRE(calls == 0);
                }
            }
        }

        GIVEN("I have 2 ScopedObserver created from it") {
            GIVEN("I release one of them") {
                WHEN("They go out of scope") {
                    {
                        ScopedObserver so(std::move(o));
                        ScopedObserver so2(so);
                        so.release();
                    }
                    THEN("I don't receive the callback") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
        }
    }
}

SCENARIO("forking a ScopedObserver") {
    GIVEN("an observer") {
        Var<int> v;
        int calls = 0;
        Observer o(v.observe([&] (int) {
            calls++;
        }));
        GIVEN("a scoped observer created from it") {
            GIVEN("a scoped observer forked from it") {
                WHEN("neither goes out of scope") {
                    ScopedObserver so{o};
                    ScopedObserver so2 = so.fork();
                    THEN("I receive the callback") {
                        v.emit(1);
                        REQUIRE(calls == 1);
                    }
                }
                WHEN("the fork goes out of scope") {
                    ScopedObserver so{o};
                    {
                        ScopedObserver so2 = so.fork();
                    }
                    THEN("I don't receive the callback") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
                WHEN("the original goes out of scope") {
                    ScopedObserver so2;
                    {
                        ScopedObserver so{o};
                        so2 = so.fork();
                    }
                    THEN("I don't receive the callback") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
                WHEN("they both go out of scope") {
                    {
                        ScopedObserver so{o};
                        ScopedObserver so2 = so.fork();
                    }
                    THEN("I don't receive the callback") {
                        v.emit(1);
                        REQUIRE(calls == 0);
                    }
                }
            }
        }
    }
}
