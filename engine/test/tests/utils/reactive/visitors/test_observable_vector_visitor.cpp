#include "catch/catch.hpp"

#include "observable_vector_visitor.h"

SCENARIO("Using ProxySlaveVisitor with an ObservableVector") {
    GIVEN("a ProxySlaveVisitor") {
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("2 ObservableVector") {
            ObservableVector<int> master;
            ObservableVector<int> slave;
            THEN("I can put them in proxy-slave mode") {
                (*visitor)(master, slave);
            }
            GIVEN("They are in proxy-slave mode") {
                (*visitor)(master, slave);
                WHEN("I change the master") {
                    master.push_back(5);
                    THEN("The slave reflects the change") {
                        REQUIRE(slave.size() == 1);
                        REQUIRE(slave[0] == 5);
                    }
                }
                GIVEN("I take them out of proxy-slave mode") {
                    visitor->remove(master);
                    WHEN("I change the master") {
                        master.push_back(5);
                        THEN("The slave doesn't makes any changes") {
                            REQUIRE(slave.size() == 0);
                        }
                    }
                }
            }
        }
        GIVEN("2 ObservableVector, with data in the master") {
            ObservableVector<int> master{2};
            ObservableVector<int> slave;
            WHEN("when I put them in proxy-slave mode") {
                (*visitor)(master, slave);
                THEN("The slave has the data") {
                    REQUIRE(slave.size() == 1);
                        REQUIRE(slave[0] == 2);
                }
            }
        }
    }
}

#include <memory>

#include "var.h"
#include "var_visitor.h"

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

SCENARIO("Using ProxySlaveVisitor with an ObservableVector with nested observables") {
    GIVEN("2 ObservableVector and a ProxySlaveVisitor") {
        ObservableVector<std::shared_ptr<TestInnerVar>> master;
        ObservableVector<std::shared_ptr<TestInnerVar>> slave;
        DataProxy dp;
        auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
        GIVEN("the master has a value") {
            master.push_back(std::make_shared<TestInnerVar>());
            WHEN("They are in proxy-slave mode") {
                (*visitor)(master, slave);
                THEN("The slave reflects the initial state of the master") {
                    REQUIRE(slave.size() == 1);
                }
            }
        }
        GIVEN("They are in proxy-slave mode") {
            (*visitor)(master, slave);
            WHEN("I change the master") {
                master.push_back(std::make_shared<TestInnerVar>());
                THEN("The slave reflects the change") {
                    REQUIRE(slave.size() == 1);
                }
            }
            GIVEN("I take them out of proxy-slave mode") {
                visitor->remove(master);
                WHEN("I change the master") {
                    master.push_back(std::make_shared<TestInnerVar>());
                    THEN("The slave doesn't makes any changes") {
                        REQUIRE(slave.size() == 0);
                    }
                }
            }
            GIVEN("There's an object in the vector") {
                auto test = std::make_shared<TestInnerVar>();
                master.push_back(test);
                WHEN("I modify the object") {
                    test->i = 5;
                    THEN("The slave object reflects the change") {
                        REQUIRE(slave.size() == 1);
                        REQUIRE(slave[0]->i.getValue() == 5);
                    }
                }
                GIVEN("I take them out of proxy-slave mode") {
                    visitor->remove(master);
                    WHEN("I modify the object") {
                        test->i = 5;
                        THEN("The slave object doesn't reflect the change") {
                            REQUIRE(slave.size() == 1);
                            REQUIRE(slave[0]->i.getValue() == 0);
                        }
                    }
                    GIVEN("I remove the object from the master") {
                        master.pop_back();
                        WHEN("I modify the object") {
                            test->i = 5;
                            THEN("The slave object doesn't reflect the change") {
                                REQUIRE(slave.size() == 1);
                                REQUIRE(slave[0]->i.getValue() == 0);
                            }
                        }
                    }
                }
            }
        }
    }
}


// TODO
// #include "data_relay.h"

// SCENARIO("Using ProxySlaveVisitor with an ObservableVector with nested observables with a data relay") {
//     GIVEN("2 ObservableVector and a ProxySlaveVisitor") {
//         ObservableVector<std::shared_ptr<TestInnerVar>> master;
//         ObservableVector<std::shared_ptr<TestInnerVar>> slave;
//         DataRelay dr;
//         auto visitor = std::make_shared<ProxySlaveVisitor>(dr.getProxy());
//         GIVEN("They are in proxy-slave mode") {
//             (*visitor)(master, slave);
//             WHEN("I change the master") {
//                 master.push_back(std::make_shared<TestInnerVar>());
//                 THEN("The slave reflects the change") {
//                     REQUIRE(slave.size() == 0);
//                 }
//             }
//             GIVEN("I take them out of proxy-slave mode") {
//                 visitor->remove(master);
//                 WHEN("I change the master") {
//                     master.push_back(std::make_shared<TestInnerVar>());
//                     THEN("The slave doesn't makes any changes") {
//                         REQUIRE(slave.size() == 0);
//                     }
//                 }
//             }
//             GIVEN("There's an object in the vector") {
//                 auto test = std::make_shared<TestInnerVar>();
//                 master.push_back(test);
//                 WHEN("I modify the object") {
//                     test->i = 5;
//                     THEN("The slave object reflects the change") {
//                         REQUIRE(slave.size() == 1);
//                         REQUIRE(slave[0]->i.getValue() == 5);
//                     }
//                 }
//                 GIVEN("I take them out of proxy-slave mode") {
//                     visitor->remove(master);
//                     WHEN("I modify the object") {
//                         test->i = 5;
//                         THEN("The slave object doesn't reflect the change") {
//                             REQUIRE(slave.size() == 1);
//                             REQUIRE(slave[0]->i.getValue() == 0);
//                         }
//                     }
//                 }
//                 GIVEN("I remove the object from the master") {
//                     master.pop_back();
//                     WHEN("I modify the object") {
//                         test->i = 5;
//                         THEN("The slave object doesn't reflect the change") {
//                             REQUIRE(slave.size() == 1);
//                             REQUIRE(slave[0]->i.getValue() == 0);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
