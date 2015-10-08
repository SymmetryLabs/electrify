#include "catch/catch.hpp"

#include <memory>

#include "weak_any_ptr.h"
#include "enable_type_erasure.h"

struct A {
    int i = 10;
    ENABLE_TYPE_ERASURE_NONVIRTUAL();
};

SCENARIO("Using WeakAnyPtr") {
    GIVEN("I have a shared_ptr") {
        std::shared_ptr<A> sharedPtr = std::make_shared<A>();
        GIVEN("I turn it into a WeakAnyPtr") {
            WeakAnyPtr wap = sharedPtr;
            THEN("The WeakAnyPtr reports that it hasn't expired") {
                REQUIRE(wap.expired() == false);
            }
            WHEN("I retrieve it while the shared_ptr is still active") {
                auto originalPtr = wap.get<A>();
                THEN("It retrieves it") {
                    REQUIRE(originalPtr != nullptr);
                    REQUIRE(originalPtr->i == 10);
                }
            }
            GIVEN("The shared_ptr has expired") {
                sharedPtr.reset();
                THEN("The WeakAnyPtr reports that it has expired") {
                    REQUIRE(wap.expired() == true);
                }
                WHEN("I retrieve it") {
                    auto originalPtr = wap.get<A>();
                    THEN("It returns nullptr") {
                        REQUIRE(originalPtr == nullptr);
                    }
                }
            }
        }
    }
}
