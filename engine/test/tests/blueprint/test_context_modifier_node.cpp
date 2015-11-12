#include <catch/catch.hpp>

#include "context_modifier_node.h"
#include "blueprint.h"
#include "test_nodes/test_node_destination.h"
#include "test_nodes/test_node_source.h"

template <typename Input>
class TestContextModifierNode : public ContextModifierNode<Input> {

public:
    static void configure(TestContextModifierNode<Input>& node, NodeHandle& handle)
    {
        ContextModifierNode<Input>::configure(node, handle);
    }

    FrameContext modifyContext(const FrameContext& original) const override
    {
        return original;
    }

private:
    NODE_IMPL();

};
REGISTER_NODE(TestContextModifierNode);

SCENARIO("Using a ContextModifierNode") {
    GIVEN("I have a ContextModifierNode and some test nodes") {
        auto blueprint = makeBlueprint();
        auto modifierNode = blueprint->makeSubnode<TestContextModifierNode>("TestContextModifierNode");

        auto sourceNode = blueprint->makeSubnode<TestNodeSource>("TestNodeSource");
        auto destinationNode = blueprint->makeSubnode<TestNodeDestination>("TestNodeDestination");

        blueprint->wireSubnodes(*sourceNode->getOutput("output"), *modifierNode->getInput("ContextModifierNode"));
        blueprint->wireSubnodes(*modifierNode->getOutput("ContextModifierNode"), *destinationNode->getInput("input"));

        blueprint->wireSubnodes(*destinationNode->getOutput("output"), *blueprint->getWirableOutput("color"));
    }
}
