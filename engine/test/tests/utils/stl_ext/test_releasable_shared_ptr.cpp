#include "catch/catch.hpp"

#include "releasable_shared_ptr.h"

SCENARIO("Using ReleasableSharedPtr") {
    GIVEN("a releasable shared pointer") {
        ReleasableSharedPtr<int> rsp{std::unique_ptr<int>{new int(5)}};
        THEN("it starts out with ownership") {
            REQUIRE(rsp);
        }
        WHEN("I release it") {
            auto released = rsp.release();
            THEN("the new pointer has ownership") {
                REQUIRE(released);
                REQUIRE(!rsp);
            }
        }
        GIVEN("I make a copy") {
            ReleasableSharedPtr<int> rsp2 = rsp;
            WHEN("they go out of scope") {
                THEN("they only release once") {
                }
            }
        }
    }
}

static int releaseCount = 0;

struct A {
    ~A() { releaseCount++; }
};

SCENARIO("ReleasableSharedPtr dtor") {
    GIVEN("a releasable shared pointer that goes out of scope") {
        {
            releaseCount = 0;
            ReleasableSharedPtr<A> rsp{std::unique_ptr<A>{new A()}};
        }
        WHEN("it goes out of scope") {
            THEN("it only releases once") {
                REQUIRE(releaseCount == 1);
            }
        }
    }
    GIVEN("a releasable shared pointer that has been copied and then goes out of scope") {
        {
            releaseCount = 0;
            ReleasableSharedPtr<A> rsp{std::unique_ptr<A>{new A()}};
            ReleasableSharedPtr<A> rsp2 = rsp;
        }
        WHEN("it goes out of scope") {
            THEN("it only releases once") {
                REQUIRE(releaseCount == 1);
            }
        }
    }
    GIVEN("a releasable shared pointer that has been copied, released, then goes out of scope") {
        std::unique_ptr<A> result;
        {
            releaseCount = 0;
            ReleasableSharedPtr<A> rsp{std::unique_ptr<A>{new A()}};
            ReleasableSharedPtr<A> rsp2 = rsp;
            result = rsp.release();
        }
        WHEN("it goes out of scope") {
            THEN("it doesn't release") {
                REQUIRE(releaseCount == 0);
                REQUIRE(result);
            }
        }
    }
}
