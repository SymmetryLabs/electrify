#include <catch/catch.hpp>

#include <boost/uuid/random_generator.hpp>
#include <cereal/archives/json.hpp>

#include "boost_uuid_serializer.h"

SCENARIO("serializing a boost::uuids::uuid") {

    GIVEN("A uuid") {
        boost::uuids::random_generator nodeUuidGenerator;
        boost::uuids::uuid i_uuid = nodeUuidGenerator();

        REQUIRE(i_uuid != boost::uuids::uuid());

        WHEN("I serialize and unserialize it") {
            std::stringstream ss;
            {
                cereal::JSONOutputArchive oarchive(ss);
                oarchive(i_uuid);
            }
            boost::uuids::uuid o_uuid;
            REQUIRE(i_uuid != o_uuid);
            {
                cereal::JSONInputArchive iarchive(ss);
                iarchive(o_uuid);
            }
            THEN("The uuids match") {
                REQUIRE(o_uuid != boost::uuids::uuid());
                REQUIRE(i_uuid == o_uuid);
            }
        }
    }

}
