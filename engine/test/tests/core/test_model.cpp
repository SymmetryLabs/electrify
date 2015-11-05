#include "catch/catch.hpp"

#include "model.h"
#include "group.h"
#include "pixel.h"
#include "data_bridge.h"
#include "proxy_slave_visitor.h"
#include "model_visitor.h"

SCENARIO("Using model in a master-slave configuration") {
    GIVEN("I have 2 models") {
        Model master;
        Model slave;
        GIVEN("Those models are in master-slave configuration with a real DataBridge") {
            DataBridge db;
            auto& dp = db.getMasterProxy();
            auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
            (*visitor)(master, slave);
            // group doesn't exist right now
            // WHEN("I add a group to the master") {
            //     auto masterGroup = std::make_shared<Group>();
            //     master.root = masterGroup;
            //     THEN("It doesn't show up immediately in the slave") {
            //         REQUIRE(slave.root.get() == nullptr);
            //     }
            //     WHEN("I flush the data bridge") {
            //         db.flushAll();
            //         THEN("The slave shows the group") {
            //             REQUIRE(slave.root.get() != nullptr);
            //         }
            //     }
            // }
            WHEN("I add a pixel to the master") {
                auto p = std::make_shared<Pixel>();
                master.pixels.push_back(p);
                REQUIRE(master.pixels.size() == 1);
                THEN("It doesn't show up immediately in the slave") {
                    REQUIRE(slave.pixels.size() == 0);
                }
                WHEN("I flush the data bridge") {
                    db.flushAll();
                    THEN("The slave shows the group") {
                        REQUIRE(slave.pixels.size() == 1);
                        REQUIRE(slave.pixels[0]);
                    }
                }
            }
        }
        GIVEN("Those models are in master-slave configuration with a fake DataBridge") {
            DataProxy dp;
            auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
            (*visitor)(master, slave);
            // group doesn't exist right now
            // WHEN("I add a group with non-default values") {
            //     master.root = std::make_shared<Group>(10, 11, 12);
            //     THEN("The slave's group shows the same values") {
            //         REQUIRE(slave.root->x == 10);
            //         REQUIRE(slave.root->y == 11);
            //         REQUIRE(slave.root->z == 12);
            //     }
            // }
        }
        GIVEN("Those models are in master-slave configuration") {
            DataProxy dp;
            auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
            (*visitor)(master, slave);
            WHEN("I set the pixels on the master") {
                auto p = std::make_shared<Pixel>();
                master.pixels = { p };
                THEN("It shows on the slave") {
                    REQUIRE(slave.pixels.size() == 1);
                    REQUIRE(slave.pixels[0] != nullptr);
                    REQUIRE(slave.pixels[0].get() != nullptr);
                }
                THEN("The slave has a new pixel object") {
                    REQUIRE(slave.pixels[0].get() != p.get());
                }
                WHEN("I change the pixel's position") {
                    p->x = 10;
                    p->y = 11;
                    p->z = 12;
                    THEN("The slave reflects the change") {
                        REQUIRE(slave.pixels[0]->x == 10);
                        REQUIRE(slave.pixels[0]->y == 11);
                        REQUIRE(slave.pixels[0]->z == 12);
                    }
                }
                GIVEN("I remove the master-slave configuration") {
                    p->x = 10;
                    REQUIRE(slave.pixels[0]->x == 10);
                    visitor->remove(master);
                    WHEN("I change the master's pixel") {
                        p->x = 15;
                        THEN("It doesn't affect the slave") {
                            REQUIRE(slave.pixels[0]->x == 10);
                        }
                    }
                }
            }
            GIVEN("I add a pixel to the master") {
                auto p = std::make_shared<Pixel>();
                master.pixels.push_back(p);
                THEN("The slave should have the pixel") {
                    REQUIRE(slave.pixels.size() == 1);
                    REQUIRE(slave.pixels[0]);
                }
            }
        }
        GIVEN("I add a pixel to the master") {
            auto p = std::make_shared<Pixel>();
            master.pixels.push_back(p);
            WHEN("I set it up in master-slave configuration") {
                DataProxy dp;
                auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
                (*visitor)(master, slave);
                THEN("The slave should start with the pixel") {
                    REQUIRE(slave.pixels.size() == 1);
                    REQUIRE(slave.pixels[0]);
                }
            }
        }
        GIVEN("I add a pixel with non-default values to the master") {
            auto p = std::make_shared<Pixel>(10, 11, 12);
            master.pixels.push_back(p);
            WHEN("I set it up in master-slave configuration") {
                DataProxy dp;
                auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
                (*visitor)(master, slave);
                THEN("The slave should start with the pixel") {
                    REQUIRE(slave.pixels.size() == 1);
                    REQUIRE(slave.pixels[0]);
                    REQUIRE(slave.pixels[0]->x == 10);
                    REQUIRE(slave.pixels[0]->y == 11);
                    REQUIRE(slave.pixels[0]->z == 12);
                }
                WHEN("I change the pixel's position") {
                    p->x = 20;
                    p->y = 21;
                    p->z = 22;
                    THEN("The slave reflects the change") {
                        REQUIRE(slave.pixels[0]->x == 20);
                        REQUIRE(slave.pixels[0]->y == 21);
                        REQUIRE(slave.pixels[0]->z == 22);
                    }
                }
            }
        }

        GIVEN("Those models are in master-slave configuration and the visitor has gone out of scope") {
            DataProxy dp;
            {
                auto visitor = std::make_shared<ProxySlaveVisitor>(dp);
                (*visitor)(master, slave);
            }
            // group doesn't exist right now
            // WHEN("I add a group to the master") {
            //     master.root = std::make_shared<Group>();
            //     THEN("It shows on the slave") {
            //         REQUIRE(slave.root.get() != nullptr);
            //     }
            // }
        }
    }
}
