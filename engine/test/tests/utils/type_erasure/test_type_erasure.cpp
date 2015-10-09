#include "catch/catch.hpp"

#include "enable_type_erasure.h"
#include "type_erasure_class.h"

struct TestNonPolymorphic {
    ENABLE_TYPE_ERASURE_NONVIRTUAL();
};

SCENARIO("Using type erasure with non-polymorphic types") {
    GIVEN("I have a type") {
        TestNonPolymorphic a;
        WHEN("I erase it") {
            THEN("It doesn't throw") {
                auto erased = eraseType(a);
            }
        }
    }
}

struct TestPolymorphicBaseA {
    virtual ~TestPolymorphicBaseA() = default;
    float f = 10;
    ENABLE_TYPE_ERASURE_BASE();
};

struct TestPolymorphicBaseB {
    virtual ~TestPolymorphicBaseB() = default;
    int i = 5;
    ENABLE_TYPE_ERASURE_BASE();
};

struct TestPolymorphicDerived : TestPolymorphicBaseA, TestPolymorphicBaseB {
    std::string s;
    ENABLE_TYPE_ERASURE();
};

SCENARIO("Using type erasure with types with multiple inheritance") {
    GIVEN("I have an instance of the derived type") {
        TestPolymorphicDerived d;
        GIVEN("I convert it to base type A") {
            TestPolymorphicBaseA& a = d;
            WHEN("I erase it") {
                THEN("It doesn't throw") {
                    auto erased = eraseType(a);
                }
            }
            GIVEN("I've erased it") {
                auto erased = eraseType(a);
                WHEN("I retrieve it as base type B") {
                    auto returned = erased->get<TestPolymorphicBaseB>();
                    THEN("It correctly retrieves it") {
                        REQUIRE(returned != nullptr);
                    }
                    THEN("It offsets the class's memory properly") {
                        REQUIRE(returned->i == 5);
                    }
                }
            }
        }
    }
}

struct TestPolymorphicImproperDerived : TestPolymorphicBaseA, TestPolymorphicBaseB {
    std::string s;
};

SCENARIO("Using type erasure with types with multiple inheritance improperly") {
    GIVEN("I have an instance of the improper derived type") {
        TestPolymorphicImproperDerived d;
        GIVEN("I convert it to base type A") {
            TestPolymorphicBaseA& a = d;
            GIVEN("I've erased it") {
                auto erased = eraseType(a);
                WHEN("I retrieve it as base type B") {
                    auto returned = erased->get<TestPolymorphicBaseB>();
                    THEN("It returns nullptr") {
                        REQUIRE(returned == nullptr);
                    }
                }
            }
        }
    }
}

struct TestNonPolymorphicWithoutEnable {
};

SCENARIO("Using type erasure without having to enable it") {
    GIVEN("I have an arithmetic type") {
        int i = 10;
        WHEN("I erase it") {
            auto erased = eraseType(i);
            THEN("It doesn't throw") {
            }
            WHEN("I try to retrieve the original") {
                auto returned = erased->get<int>();
                THEN("It correctly retrieves it") {
                    REQUIRE(returned != nullptr);
                    REQUIRE(*returned == 10);
                }
            }
        }
    }
    GIVEN("I have a non-polymorphic type") {
        TestNonPolymorphicWithoutEnable a;
        WHEN("I erase it") {
            auto erased = eraseType(a);
            THEN("It doesn't throw") {
            }
            WHEN("I try to retrieve the original") {
                auto returned = erased->get<TestNonPolymorphicWithoutEnable>();
                THEN("It correctly retrieves it") {
                    REQUIRE(returned != nullptr);
                }
            }
        }
    }
}
