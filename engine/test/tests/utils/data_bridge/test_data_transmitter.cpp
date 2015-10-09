#include "catch/catch.hpp"

#include "data_transmitter.h"
#include "test_access.h"
#include "data_bridge.h"
#include "data_proxy.h"

DEF_ACCESS(sendCommand, template sendCommand<int>);

SCENARIO("Using a data transmitter") {
    GIVEN("I have a data transmitter") {
        std::shared_ptr<int> dest = std::make_shared<int>(10);
        DataTransmitter dt(dest);
        WHEN("I send a command") {
            int i = 0;
            call<sendCommand>(dt, [&] (const std::shared_ptr<int>&) {
                i++;
            });
            THEN("it executes immediately") {
                REQUIRE(i == 1);
            }
        }
        GIVEN("I add data proxies") {
            DataBridge db;
            dt.setDataProxies(db.getMasterProxy(), db.getSlaveProxy());
            WHEN("I send a command") {
                int i = 0;
                call<sendCommand>(dt, [&] (const std::shared_ptr<int>&) {
                    i++;
                });
                THEN("it doesn't executes immediately") {
                    REQUIRE(i == 0);
                }
                WHEN("I flush the bridge") {
                    db.flushAll();
                    THEN("It executes") {
                        REQUIRE(i == 1);
                    }
                }
            }
        }
    }
}
