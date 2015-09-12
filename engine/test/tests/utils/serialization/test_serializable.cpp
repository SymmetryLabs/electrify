// #include <catch/catch.hpp>

// #include <regex>
// #include <sstream>

// #include <cereal/archives/json.hpp>
// #include <cereal/types/boost_variant.hpp>
// #include <cereal/types/map.hpp>

// #include "serializable.h"
// #include "serializers.h"

// #include "test_serializable_data.h"

// SCENARIO("using Serializable") {
//     GIVEN("I have a Serializable") {
//         Serializable s;
//         WHEN("I serialize it") {
//             std::stringstream ss;
//             {
//                 cereal::JSONOutputArchive oarchive(ss);
//                 oarchive(s);
//             }
//             THEN("It contains the data") {
//                 CAPTURE(ss.str());
//                 REQUIRE(std::regex_search(ss.str(), r));
//             }
//             WHEN("I unserialize it") {
//                 Serializable s2;
//                 {
//                     cereal::JSONInputArchive iarchive(ss);
//                     iarchive(s2);
//                 }
//                 THEN("It contains the same data") {
//                     REQUIRE(s.uuid == s2.uuid);
//                 }
//             }
//         }
//     }
// }
