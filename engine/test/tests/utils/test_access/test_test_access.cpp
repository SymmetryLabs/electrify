#include <catch/catch.hpp>

#include "enable_test_access.h"
#include "test_access.h"

struct A {
private:
    int f() { return 5; }
    template <typename T>
    T t() { return {}; }
    int v = 10;
    ENABLE_TEST_ACCESS();
};

DEF_ACCESS(f, f);
DEF_ACCESS(t, template t<int>);
DEF_ACCESS(v, v);

SCENARIO("Gaining test access") {
    GIVEN("A class with private member functions and test access enabled") {
        A a;
        WHEN("I try to access a function") {
            int i = TestAccess<f>::call(a);
            THEN("It works") {
                REQUIRE(i == 5);
            }
        }
        WHEN("I try to access a template function") {
            int i = TestAccess<t>::call(a);
            THEN("It works") {
                REQUIRE(i == 0);
            }
        }
        WHEN("I try to access a variable function") {
            int i = TestAccess<v>::access(a);
            THEN("It works") {
                REQUIRE(i == 10);
            }
        }
        WHEN("I try to access a function using the helper") {
            int i = call<f>(a);
            THEN("It works") {
                REQUIRE(i == 5);
            }
        }
        WHEN("I try to access a template function using the helper") {
            int i = call<t>(a);
            THEN("It works") {
                REQUIRE(i == 0);
            }
        }
        WHEN("I try to access a variable using the helper") {
            int i = access<v>(a);
            THEN("It works") {
                REQUIRE(i == 10);
            }
        }
    }
}
