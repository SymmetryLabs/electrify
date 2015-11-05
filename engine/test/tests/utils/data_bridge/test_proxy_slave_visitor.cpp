#include "catch/catch.hpp"

#include "proxy_slave_visitor.h"

SCENARIO("using ProxySlaveVisitor with a shared_ptr") {
    GIVEN("a ProxySlaveVisitor") {
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("2 empty shared_ptrs") {
            std::shared_ptr<int> master;
            std::shared_ptr<int> slave;
            WHEN("I put them in master-slave configuration") {
                (*visitor)(master, slave);
                THEN("they are both still empty") {
                    REQUIRE(!master);
                    REQUIRE(!slave);
                }
            }
        }
    }
}
