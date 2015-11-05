#include "catch/catch.hpp"

#include "data_relay.h"

SCENARIO("Using DataRelay to broadcast to multiple outgoing data relays") {
    GIVEN("2 DataRelays: master and aux") {
        DataRelay relayMaster;
        DataRelay relayAux;
        relayMaster.addAuxOutgoingDataRelay(relayAux.getOutgoingDataRelay());

        GIVEN("There are events in the queue") {
            int iMaster = 0;
            relayMaster.getProxy().sendEvent([&] { iMaster++; });
            int iAux = 0;
            relayAux.getProxy().sendEvent([&] { iAux++; });
            relayMaster.commitOutgoingTransaction();
            WHEN("I process the master relay") {
                relayMaster.processIncomingTransactions();
                THEN("The master event gets called") {
                    REQUIRE(iMaster == 1);
                    REQUIRE(iAux == 0);
                }
            }
            WHEN("I process the aux relay") {
                relayAux.processIncomingTransactions();
                THEN("The aux event gets called") {
                    REQUIRE(iAux == 1);
                    REQUIRE(iMaster == 0);
                }
            }
        }

        GIVEN("There are 2 events in the queue") {
            int iMaster = 0;
            int iAux = 0;

            relayMaster.getProxy().sendEvent([&] { iMaster++; });
            relayAux.getProxy().sendEvent([&] { iAux++; });
            relayMaster.commitOutgoingTransaction();

            relayMaster.getProxy().sendEvent([&] { iMaster++; });
            relayAux.getProxy().sendEvent([&] { iAux++; });
            relayMaster.commitOutgoingTransaction();
            WHEN("I process the master relay") {
                relayMaster.processIncomingTransactions();
                THEN("2 master events get called") {
                    REQUIRE(iMaster == 2);
                    REQUIRE(iAux == 0);
                }
            }
            WHEN("I process the aux relay") {
                relayAux.processIncomingTransactions();
                THEN("2 aux events get called") {
                    REQUIRE(iAux == 2);
                    REQUIRE(iMaster == 0);
                }
            }
            WHEN("I process the master relay up to transaction 1") {
                relayMaster.processIncomingTransactionsUpTo(1);
                THEN("1 master event gets called") {
                    REQUIRE(iMaster == 1);
                    REQUIRE(iAux == 0);
                }
            }
            WHEN("I process the aux relay up to transaction 1") {
                relayAux.processIncomingTransactionsUpTo(1);
                THEN("1 aux event gets called") {
                    REQUIRE(iAux == 1);
                    REQUIRE(iMaster == 0);
                }
            }
        }

        GIVEN("I commit the outgoing transaction") {
            relayMaster.getProxy().sendEvent([&] {});
            relayAux.getProxy().sendEvent([&] {});
            relayMaster.commitOutgoingTransaction();
            WHEN("I process the master relay") {
                auto transactionId = relayMaster.processIncomingTransactions();
                THEN("The transaction id is 1") {
                    REQUIRE(transactionId == 1);
                }
            }
            WHEN("I process the aux relay") {
                auto transactionId = relayAux.processIncomingTransactions();
                THEN("The transaction id is 1") {
                    REQUIRE(transactionId == 1);
                }
            }
        }

        GIVEN("I commit 2 outgoing transactions") {
            relayMaster.getProxy().sendEvent([&] {});
            relayAux.getProxy().sendEvent([&] {});
            relayMaster.commitOutgoingTransaction();

            relayMaster.getProxy().sendEvent([&] {});
            relayAux.getProxy().sendEvent([&] {});
            relayMaster.commitOutgoingTransaction();
            WHEN("I process the master relay") {
                auto transactionId = relayMaster.processIncomingTransactions();
                THEN("The transaction id is 2") {
                    REQUIRE(transactionId == 2);
                }
            }
            WHEN("I process the aux relay") {
                auto transactionId = relayAux.processIncomingTransactions();
                THEN("The transaction id is 2") {
                    REQUIRE(transactionId == 2);
                }
            }
        }
    }
}
