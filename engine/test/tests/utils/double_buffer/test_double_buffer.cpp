#include "catch/catch.hpp"

#include "double_buffer.h"

SCENARIO("Using DoubleBuffer") {
    GIVEN("a DoubleBuffer<int>") {
        DoubleBuffer<int> db;
        std::vector<int> arr;
        THEN("the back buffer starts with array size 0") {
            REQUIRE(db.getBackBuffer().size() == 0);
        }
        THEN("the front buffer starts with array size 0") {
            db.copyBuffer(arr);
            REQUIRE(arr.size() == 0);
        }
        WHEN("I set the size") {
            db.setSize(10);
            db.getBackBuffer()[0] = 5;
            THEN("the back buffer immediately shows the new size") {
                REQUIRE(db.getBackBuffer().size() == 10);
                REQUIRE(db.getBackBuffer()[0] == 5);
            }
            THEN("the front buffer still works with array size 0") {
                db.copyBuffer(arr);
                REQUIRE(arr.size() == 0);
            }
            WHEN("I swap the buffers") {
                db.swapBuffers();
                THEN("the front buffer works with an array of the new size") {
                    arr.resize(10);
                    db.copyBuffer(arr);
                    REQUIRE(arr.size() == 10);
                    REQUIRE(arr[0] == 5);
                }
            }
        }
    }
}

SCENARIO("Using DoubleBuffer with id check") {
    GIVEN("a DoubleBuffer<int>") {
        DoubleBuffer<int> db{2};
        std::vector<int> v{0, 0};
        GIVEN("I fill the back buffer, set the id, and swap buffers") {
            db.getBackBuffer()[0] = 10;
            db.setId(15);
            db.swapBuffers();
            WHEN("I try to copy with the wrong id") {
                db.copyBuffer(14, v);
                THEN("It doesn't copy") {
                    REQUIRE(v[0] == 0);
                }
            }
            WHEN("I try to copy with the right id") {
                db.copyBuffer(15, v);
                THEN("It doesn't copy") {
                    REQUIRE(v[0] == 10);
                }
            }
        }
    }
}
