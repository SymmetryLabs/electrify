template<typename Input>
BlueprintNode<Input>::BlueprintNode(Blueprint& nodeHandle)
: CompoundNode<Input>(nodeHandle)
{
    nodeHandle.setName("Blueprint");
    nodeHandle.registerWirableOutput("color", &output);
}
