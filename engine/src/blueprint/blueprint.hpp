template <typename Input>
void BlueprintNode<Input>::configure(BlueprintNode<Input>& node, CompoundNodeHandle& handle)
{
    CompoundNode<Input>::configure(node, handle);
    handle.setName("Blueprint");
    handle.registerWirableOutput("color", node.generateWirableOutput(&node.output));
}
