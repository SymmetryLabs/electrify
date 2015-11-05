#include "catch/catch.hpp"

#include "var.h"
#include "var_visitor.h"

SCENARIO("Using Var with a ProxySlaveVisitor") {
    GIVEN("a ProxySlaveVisitor") {
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("2 ObservableVectors") {
            Var<int> master;
            Var<int> slave;
            THEN("I can put them in proxy-slave mode") {
                (*visitor)(master, slave);
            }
            GIVEN("They are in proxy-slave mode") {
                (*visitor)(master, slave);
                WHEN("I change the master") {
                    master = 5;
                    THEN("The slave reflects the change") {
                        REQUIRE(slave == 5);
                    }
                }
                GIVEN("I take them out of proxy-slave mode") {
                    visitor->remove(master);
                    WHEN("I change the master") {
                        master = 5;
                        THEN("The slave doesn't makes any changes") {
                            REQUIRE(slave == 0);
                        }
                    }
                }
            }
        }
        GIVEN("2 ObservableVector where the master has a default value") {
            Var<int> master{2};
            Var<int> slave;
            WHEN("I put them in proxy-slave mode") {
                (*visitor)(master, slave);
                THEN("The slave reflects the initial value") {
                    REQUIRE(slave == 2);
                }
            }
            GIVEN("They are in proxy-slave mode") {
                (*visitor)(master, slave);
                WHEN("I change the master") {
                    master = 5;
                    THEN("The slave reflects the change") {
                        REQUIRE(slave == 5);
                    }
                }
                GIVEN("I take them out of proxy-slave mode") {
                    visitor->remove(master);
                    WHEN("I change the master") {
                        master = 5;
                        THEN("The slave doesn't makes any changes") {
                            REQUIRE(slave == 2);
                        }
                    }
                }
            }
        }
        GIVEN("2 ObservableVector where the slave has a default value") {
            Var<int> master;
            Var<int> slave{2};
            WHEN("I put them in proxy-slave mode") {
                (*visitor)(master, slave);
                THEN("The slave reflects the initial value") {
                    REQUIRE(slave == 0);
                }
            }
            GIVEN("They are in proxy-slave mode") {
                (*visitor)(master, slave);
                WHEN("I change the master") {
                    master = 5;
                    THEN("The slave reflects the change") {
                        REQUIRE(slave == 5);
                    }
                }
                GIVEN("I take them out of proxy-slave mode") {
                    visitor->remove(master);
                    WHEN("I change the master") {
                        master = 5;
                        THEN("The slave doesn't makes any changes") {
                            REQUIRE(slave == 0);
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("ProxySlaveVisitor with nested Vars") {
    GIVEN("a ProxySlaveVisitor") {
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("2 Var of Vars in master-slave configuration") {
            Var<std::shared_ptr<Var<int>>> master;
            Var<std::shared_ptr<Var<int>>> slave;
            (*visitor)(master, slave);
            GIVEN("I add a var to master") {
                auto v1Master = std::make_shared<Var<int>>(5);
                master.emit(v1Master);
                THEN("the slave has a copy") {
                    REQUIRE(slave.getValue());
                    REQUIRE(slave.getValue() != v1Master);
                    REQUIRE(slave.getValue()->getValue() == 5);
                }
                auto v1Slave = slave.getValue();
                WHEN("I emit to the value of the master") {
                    v1Master->emit(6);
                    THEN("the value of the slave has the same value") {
                        REQUIRE(v1Slave->getValue() == 6);
                    }
                }
                GIVEN("I add another var to master") {
                    auto v2Master = std::make_shared<Var<int>>(10);
                    master.emit(v2Master);
                    THEN("The slave has a copy of the new var") {
                        REQUIRE(slave.getValue()->getValue() == 10);
                        REQUIRE(slave.getValue() != v1Slave);
                    }
                    WHEN("I emit to the master's var") {
                        v2Master->emit(11);
                        THEN("the slave's new var has the value") {
                            REQUIRE(slave.getValue()->getValue() == 11);
                        }
                        THEN("the slave's old var doesn't have the value") {
                            REQUIRE(v1Slave->getValue() == 5);
                        }
                    }
                }
            }
        }
    }
}

struct TestInnerVar {
    Var<int> i;
};

template <typename Visitor, typename... TestType,
    typename enable_if_all<int, are_same<TestInnerVar, typename std::decay<TestType>::type...>::value>::type = 0>
auto performOnObjects(Visitor& visitor, TestType&&... obj)
    -> decltype(visitor(obj.i...))
{
    return visitor(obj.i...);
}

SCENARIO("Using ProxySlaveVisitor with var inside another object") {
    GIVEN("2 objects and a ProxySlaveVisitor") {
        TestInnerVar master;
        TestInnerVar slave;
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        WHEN("They are put in proxy-slave mode") {
            (*visitor)(master, slave);
        }
    }
}

SCENARIO("Using ProxySlaveVisitor with var inside another object ptr") {
    GIVEN("2 objects and a ProxySlaveVisitor") {
        auto master = std::make_shared<TestInnerVar>();
        auto slave = std::make_shared<TestInnerVar>();
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        WHEN("They are put in proxy-slave mode") {
            (*visitor)(master, slave);
        }
    }
}

struct TestEmpty {
};

template <typename Visitor, typename... TestType,
    typename enable_if_all<int, are_same<TestEmpty, typename std::decay<TestType>::type...>::value>::type = 0>
void performOnObjects(Visitor& visitor, TestType&&... obj)
{
}

SCENARIO("Using ProxySlaveVisitor with an object ptr") {
    GIVEN("2 objects and a ProxySlaveVisitor") {
        auto master = std::make_shared<TestEmpty>();
        auto slave = std::make_shared<TestEmpty>();
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        WHEN("They are put in proxy-slave mode") {
            (*visitor)(master, slave);
        }
    }
}

#include "data_relay.h"

SCENARIO("Using Var with a ProxySlaveVisitor with scope issues") {
    GIVEN("a var") {
        Var<int> v1;
        GIVEN("a data proxy") {
            DataProxy dp;
            GIVEN("a second var that observes the first and then goes out of scope") {
                {
                    Var<int> v2;
                    auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
                    (*visitor)(v1, v2);
                }
                WHEN("the first emits a value") {
                    v1.emit(5);
                    THEN("it has the value") {
                        REQUIRE(v1.getValue() == 5);
                    }
                }
            }
            GIVEN("a second var that the first one observes and then goes out of scope") {
                {
                    Var<int> v2;
                    auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
                    (*visitor)(v2, v1);
                }
                WHEN("the first emits a value") {
                    v1.emit(5);
                    THEN("it has the value") {
                        REQUIRE(v1.getValue() == 5);
                    }
                }
            }
        }
        GIVEN("a data relay") {
            DataRelay dr;
            GIVEN("a second var that observes the first and then goes out of scope") {
                {
                    Var<int> v2;
                    auto visitor = std::make_shared<ProxySlaveVisitor>(dr.getProxy());
                    (*visitor)(v1, v2);
                }
                WHEN("the first emits a value and the relay is flushed") {
                    v1.emit(5);
                    dr.flush();
                    THEN("it has the value") {
                        REQUIRE(v1.getValue() == 5);
                    }
                }
            }
            GIVEN("a second var that the first one observes and then goes out of scope") {
                {
                    Var<int> v2;
                    auto visitor = std::make_shared<ProxySlaveVisitor>(dr.getProxy());
                    (*visitor)(v2, v1);
                    v1.emit(4);
                }
                THEN("it has the value") {
                    REQUIRE(v1.getValue() == 4);
                }
                WHEN("the first emits a value and the relay is flushed") {
                    v1.emit(5);
                    dr.flush();
                    THEN("it has the value") {
                        REQUIRE(v1.getValue() == 5);
                    }
                }
            }
            GIVEN("a proxy slave visitor") {
                auto visitor = std::make_shared<ProxySlaveVisitor>(dr.getProxy());
                GIVEN("a second var that observes the first and then goes out of scope") {
                    {
                        Var<int> v2;
                        (*visitor)(v1, v2);
                    }
                    WHEN("the first emits a value and the relay is flushed") {
                        v1.emit(5);
                        dr.flush();
                        THEN("it has the value") {
                            REQUIRE(v1.getValue() == 5);
                        }
                    }
                }
                GIVEN("a second var that the first one observes and then goes out of scope") {
                    {
                        Var<int> v2;
                        (*visitor)(v2, v1);
                    }
                    THEN("it has the value") {
                        REQUIRE(v1.getValue() == 0);
                    }
                    WHEN("the first emits a value and the relay is flushed") {
                        v1.emit(5);
                        dr.flush();
                        THEN("it has the value") {
                            REQUIRE(v1.getValue() == 5);
                        }
                    }
                }
            }
        }
    }
}
