/*
  ==============================================================================

    SelectionContainer.h
    Created: 18 Aug 2015 4:30:05pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include "SelectionController.h"

class SelectionContainer {

public:
    SelectionContainer();
    virtual ~SelectionContainer() {}
    
    SelectionController selectionController;
    
private:
    friend class SelectionController;
    
};
