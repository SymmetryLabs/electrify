#pragma once

#include "blueprint_project.h"
#include "blueprint.h"
#include "model.h"
#include "basic_node.h"
#include "color.h"

template <typename Input>
struct TestIncrementer : public BasicNode<Skip<Input, 1>, Color> {
    static void configure(TestIncrementer<Input>& node, NodeHandle& handle)
    { BasicNode<Skip<Input, 1>, Color>::configure(node, handle); }

    void init() override { increment = 0; }
    void update(const FrameContext& frame) override { increment = (increment + 1) % 0x100; }
    Color calculate(const FrameContext& frame) const override { return Color(increment); }

    int increment = 0;
    NODE_IMPL();
};
REGISTER_NODE(TestIncrementer);

unique_ptr<BlueprintProject> projectTestData();
