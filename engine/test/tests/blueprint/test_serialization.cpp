#include "catch/catch.hpp"

#include <sstream>

#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include "node.h"
#include "node_handle.h"
#include "node_handle_serializer.h"

template<typename Input>
struct TestNode : Node {
    static void configure(TestNode& node, NodeHandle& handle) {
        Node::configure(node, handle);
        handle.setName("TestNode");
    }
};
REGISTER_NODE(TestNode);

SCENARIO("Deserializing a node") {
    GIVEN("I have a serialized node that has a custom name for that instance") {
        auto handle = makeNodeHandle<TestNode>("TestNode");
        handle->setName("NewName");
        std::stringstream ss;
        {
            cereal::JSONOutputArchive oarchive(ss);
            oarchive(handle);
        }
        WHEN("I deserialize the node") {
            shared_ptr<NodeHandle> deserializedHandle;
            {
                cereal::JSONInputArchive iarchive(ss);
                iarchive(deserializedHandle);
            }
            THEN("It restores the custom name") {
                CAPTURE(ss.str());
                REQUIRE(deserializedHandle->getName() == "NewName");
            }
        }
    }
}