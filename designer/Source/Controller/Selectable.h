/*
  ==============================================================================

    Selectable.h
    Created: 17 Aug 2015 3:15:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

class SelectionContainer;
class SelectionController;

class Selectable {
    
public:
    explicit Selectable(SelectionController* selectionController);
    explicit Selectable(SelectionContainer* selectionContainer);
    virtual ~Selectable() {}
    
    Var<bool> selected;
    
    void setSelected(bool selected);
    
    virtual void deleteSelectable();
    
private:
    SelectionController* selectionController;

};
