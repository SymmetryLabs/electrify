/*
  ==============================================================================

    ComponentUtils.h
    Created: 1 Sep 2015 3:58:47pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once

template<typename ChildFilterType>
Component* getComponentAtWithChildTypeFilter(Component* parent, Point<int> position)
{
    for (int i = 0; i < parent->getNumChildComponents(); i++) {
        Component* childComponent = parent->getChildComponent(i);
        if (dynamic_cast<ChildFilterType*>(childComponent)) {
            Point<int> childPoint = childComponent->getLocalPoint(parent, position);
            Component* component = childComponent->getComponentAt(childPoint);
            if (component) {
                return component;
            }
        }
    }
    return nullptr;
}
