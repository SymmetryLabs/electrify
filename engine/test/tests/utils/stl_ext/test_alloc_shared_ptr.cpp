#include <catch/catch.hpp>

#include "alloc_shared_ptr.h"

SCENARIO("using allocSharedPtr", "[!throws]") {
    WHEN("I alloc a shared_ptr") {
        THEN("The ptr is correct") {
            void* addr = nullptr;
            auto ptr = allocSharedPtr<int>([&] (std::shared_ptr<int> i) {
                addr = i.get();
            });
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr<string>") {
        THEN("The ptr is correct") {
            void* addr = nullptr;
            auto ptr = allocSharedPtr<std::string>([&] (std::shared_ptr<std::string> i) {
                addr = i.get();
            });
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr with a custom class") {
        struct Test {
            int i = 0;
        };
        void* addr = nullptr;
        auto ptr = allocSharedPtr<Test>([&] (std::shared_ptr<Test> i) {
            addr = i.get();
        });
        THEN("The ptr is correct") {
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr with a polymorphic class") {
        struct Test {
            int i = 0;
        };
        struct Test2 : Test {
            int i2 = 0;
        };
        void* addr = nullptr;
        auto ptr = allocSharedPtr<Test2>([&] (std::shared_ptr<Test2> i) {
            addr = i.get();
        });
        THEN("The ptr is correct") {
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr with a class inheriting from enable_shared_from_this") {
        struct Test : std::enable_shared_from_this<Test> {
            int i = 1;
        };
        void* addr = nullptr;
        auto ptr = allocSharedPtr<Test>([&] (std::shared_ptr<Test> i) {
            addr = i.get();
        });
        THEN("The ptr is correct") {
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
            REQUIRE(ptr->shared_from_this().get() == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr with a class inheriting from enable_shared_from_this") {
        struct Test : std::enable_shared_from_this<Test> {
            int i = 1;
            Test() : i(2) {}
        };
        auto ptr = allocSharedPtr<Test>([&] (std::shared_ptr<Test> i) {});
        THEN("The state constructed in the constructor stays intact") {
            REQUIRE(ptr->i == 2);
        }
    }

    WHEN("I alloc a shared_ptr with a class inheriting from enable_shared_from_this of as base class") {
        struct Test : std::enable_shared_from_this<Test> {
            int i = 0;
        };
        struct Test2 : Test {
            int i2 = 0;
        };
        void* addr = nullptr;
        auto ptr = allocSharedPtr<Test2>([&] (std::shared_ptr<Test2> i) {
            addr = i.get();
        });
        THEN("The ptr is correct") {
            REQUIRE(ptr);
            REQUIRE(ptr.get() != nullptr);
            REQUIRE(addr == ptr.get());
            REQUIRE(ptr->shared_from_this().get() == ptr.get());
        }
    }
    WHEN("I alloc a shared_ptr with a class inheriting from enable_shared_from_this") {
        struct Test : std::enable_shared_from_this<Test> {
            int i = 1;
            Test() : i(2) {}
        };
        struct Test2 : Test {
            int i2 = 3;
            Test2() : i2(4) {}
        };
        auto ptr = allocSharedPtr<Test2>([&] (std::shared_ptr<Test2> i) {});
        THEN("The state constructed in the constructor stays intact") {
            REQUIRE(ptr->i == 2);
            REQUIRE(ptr->i2 == 4);
        }
    }

    WHEN("The constructor throws an exception") {
        THEN("The callback gets called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                Test() {
                    throw std::exception();
                }
            };
            REQUIRE_THROWS_AS(allocSharedPtr<Test>([] (std::shared_ptr<Test>) {
                calls++;
            }), std::exception);
            REQUIRE(calls == 1);
        }
        THEN("The destructor doesn't get called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                Test() {
                    throw std::exception();
                }
                ~Test() {
                    calls++;
                }
            };
            REQUIRE_THROWS_AS(allocSharedPtr<Test>([] (std::shared_ptr<Test>) {}), std::exception);
            REQUIRE(calls == 0);
        }
    }
    WHEN("The callback throws an exception") {
        THEN("The constructor doesn't get called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                Test() {
                    calls++;
                }
            };
            REQUIRE_THROWS_AS(allocSharedPtr<Test>([] (std::shared_ptr<Test>) {
                throw std::exception();
            }), std::exception);
            REQUIRE(calls == 0);
        }
        THEN("The destructor doesn't get called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                ~Test() {
                    calls++;
                }
            };
            REQUIRE_THROWS_AS(allocSharedPtr<Test>([] (std::shared_ptr<Test>) {
                throw std::exception();
            }), std::exception);
            REQUIRE(calls == 0);
        }
    }
    WHEN("Nothing throws an exception") {
        THEN("The constructor gets called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                Test() {
                    calls++;
                }
            };
            allocSharedPtr<Test>([] (std::shared_ptr<Test>) {});
            REQUIRE(calls == 1);
        }
        THEN("The destructor gets called") {
            static int calls = 0;
            struct Test {
                int i = 0;
                ~Test() {
                    calls++;
                }
            };
            allocSharedPtr<Test>([] (std::shared_ptr<Test>) {});
            REQUIRE(calls == 1);
        }
    }
}
