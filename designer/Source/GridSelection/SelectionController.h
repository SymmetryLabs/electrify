/*
  ==============================================================================

    SelectionController.h
    Created: 17 Aug 2015 3:15:27pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include "juce_KeyListener.h"

#include "Selectable.h"

class SelectionContainer;

class SelectionController : public KeyListener {
    
public:
    explicit SelectionController(SelectionContainer* selectionContainer);
    
    bool hasSelection() const;
    
    void select(Selectable* item);
    void toggleSelected(Selectable* item, bool enableMulti = false);
    void setSelected(const vector<Selectable*>& items);
    
    void deselect(Selectable* item);
    void deselectAll();
    
    void deleteSelected();
    
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;

private:
    SelectionContainer* selectionContainer;
    
    vector<Selectable*> selectedItems;
    
};
