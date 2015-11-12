#include "catch/catch.hpp"

#include "compound_node.h"
#include "blueprint.h"
#include "data_bridge.h"

template <typename Input>
class TestNodeBlank : public Node {};
REGISTER_NODE(TestNodeBlank);

SCENARIO("Adding a node") {
    GIVEN("I have a CompoundNode") {
        auto blueprint = makeBlueprint();
        auto compound = blueprint->makeSubnode<CompoundNode>("CompoundNode");
        WHEN("I add a node B to the node handle A") {
            compound->createSubnode("TestNodeBlank");
            THEN("The corresponding node A shows the new node B") {
                auto& node = compound->getNode<CompoundNode>();
                REQUIRE(node.getNumSubnodes() == 1);
            }
        }
        GIVEN("I have added the DataBridge") {
            DataBridge db;
            auto renderable = blueprint->releaseRenderable(db);
            WHEN("I add a node B to the node handle A") {
                compound->createSubnode("TestNodeBlank");
                THEN("The corresponding node A doesn't have the node B right away") {
                    auto& node = compound->getNode<CompoundNode>();
                    REQUIRE(node.getNumSubnodes() == 0);
                }
                WHEN("I clear the bridge") {
                    db.flushAll();
                    THEN("The corresponding node A shows the new node B") {
                        auto& node = compound->getNode<CompoundNode>();
                        REQUIRE(node.getNumSubnodes() == 1);
                    }
                }
                GIVEN("The engine side gets cleared") {
                    auto& node = compound->getNode<CompoundNode>();
                    std::weak_ptr<NodeHandle> weakHandle = blueprint->subnodes.at(0);
                    REQUIRE(!weakHandle.expired());
                    blueprint.reset();
                    REQUIRE(weakHandle.expired());

                    WHEN("I clear the bridge") {
                        db.flushAll();
                        THEN("The corresponding node A shows the new node B") {
                            REQUIRE(node.getNumSubnodes() == 1);
                        }
                    }
                }
            }
        }
    }
}
