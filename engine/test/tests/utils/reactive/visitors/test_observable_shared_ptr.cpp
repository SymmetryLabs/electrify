#include "catch/catch.hpp"

#include "observable_shared_ptr_visitor.h"

SCENARIO("Using ProxySlaveVisitor with ObservableSharedPtr") {
    GIVEN("a ProxySlaveVisitor") {
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("2 ObservableSharedPtr's") {
            ObservableSharedPtr<int> master;
            ObservableSharedPtr<int> slave;
            THEN("I can put them in proxy-slave mode") {
                (*visitor)(master, slave);
            }
        }
    }
}
