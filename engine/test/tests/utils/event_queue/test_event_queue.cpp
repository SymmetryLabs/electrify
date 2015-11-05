#include <catch/catch.hpp>

#include "event_queue.h"

SCENARIO("Using EventQueue") {
    GIVEN("I have an event queue") {
        EventQueue eq;
        WHEN("I queue an event") {
            int i = 0;
            eq.queueEvent([&] {
                i++;
            });
            THEN("It doesn't execute right away") {
                REQUIRE(i == 0);
            }
            WHEN("I flush the queue") {
                eq.flush();
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I flush the queue twice") {
                eq.flush();
                eq.flush();
                THEN("It only executes once") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I commit the transaction") {
                eq.commitTransaction();
                THEN("It doesn't execute right away") {
                    REQUIRE(i == 0);
                }
                WHEN("I process the transaction") {
                    eq.processTransactions();
                    THEN("It executes") {
                        REQUIRE(i == 1);
                    }
                }
            }
        }
    }
}

SCENARIO("Using EventQueue with transaction ids") {
    GIVEN("I have an event queue with a queued event") {
        EventQueue eq;
        int i = 0;
        eq.queueEvent([&] {
            i++;
        });
        WHEN("I commit the transaction with an id") {
            eq.commitTransaction(5);
            THEN("It doesn't execute right away") {
                REQUIRE(i == 0);
            }
            WHEN("I process the transaction") {
                auto id = eq.processTransactions();
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
                THEN("the id is the id of the transaction that just executed") {
                    REQUIRE(id == 5);
                }
            }
            WHEN("I process the transaction with a lower id") {
                eq.processTransactionsUpTo(4);
                THEN("It doesn't execute") {
                    REQUIRE(i == 0);
                }
            }
            WHEN("I process the transaction with the same id") {
                eq.processTransactionsUpTo(5);
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I process the transaction with a higher id") {
                eq.processTransactionsUpTo(6);
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
        }
    }
    GIVEN("I have an event queue") {
        EventQueue eq;
        WHEN("I commit the transaction with an id but no events") {
            eq.commitTransaction(5);
            WHEN("I process the transaction") {
                auto id = eq.processTransactions();
                THEN("It returns the last transaction id") {
                    REQUIRE(id == 0);
                }
            }
            THEN("I can process the transaction with a lower id") {
                eq.processTransactionsUpTo(4);
            }
            THEN("I can process the transaction with the same id") {
                eq.processTransactionsUpTo(5);
            }
            THEN("I can process the transaction with a higher id") {
                eq.processTransactionsUpTo(6);
            }
        }
    }
}

SCENARIO("Integer overflow with EventQueue") {
    GIVEN("I have an event queue with a queued event") {
        EventQueue eq;
        int i = 0;
        eq.queueEvent([&] {
            i++;
        });
        WHEN("I commit the transaction with an id near int max") {
            unsigned int id = UINT_MAX - 3;
            eq.commitTransaction(id);
            THEN("It doesn't execute right away") {
                REQUIRE(i == 0);
            }
            WHEN("I process the transaction") {
                eq.processTransactions();
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I process the transaction with an id that has overflowed") {
                eq.processTransactionsUpTo(UINT_MAX + 3);
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
        }
        WHEN("I commit the transaction with an id that has overflowed") {
            eq.commitTransaction(UINT_MAX + 3);
            THEN("It doesn't execute right away") {
                REQUIRE(i == 0);
            }
            WHEN("I process the transaction") {
                eq.processTransactions();
                THEN("It executes") {
                    REQUIRE(i == 1);
                }
            }
            WHEN("I process the transaction with an id that hasn't") {
                eq.processTransactionsUpTo(UINT_MAX - 3);
                THEN("It doesn't execute") {
                    REQUIRE(i == 0);
                }
            }
        }
    }
}