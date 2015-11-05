#include "catch/catch.hpp"

#include "data_bridge.h"

SCENARIO("Using a Databridge with an outgoing transaction with an id") {
    GIVEN("a DataBridge") {
        DataBridge db;
        GIVEN("a committed outgoing transaction") {
            auto& dp = db.getMasterProxy();
            int count = 0;
            dp.sendEvent([&] { count++; });
            auto& dr = db.getMasterRelay();
            dr.commitOutgoingTransaction();
            THEN("the outgoing data relay used the correct frame id") {
                REQUIRE(dr.getLastFrameId() == 1);
            }
            auto& slaveDR = db.getSlaveRelay();
            WHEN("the slave relay processes all transactions") {
                auto id = slaveDR.processIncomingTransactions();
                THEN("It receives the same frame id") {
                    REQUIRE(id == 1);
                }
                THEN("the event got processed") {
                    REQUIRE(count == 1);
                }
            }
            WHEN("the slave relay processes transactions up to the frame id") {
                slaveDR.processIncomingTransactionsUpTo(1);
                THEN("the event got processed") {
                    REQUIRE(count == 1);
                }
            }
        }
    }
}
