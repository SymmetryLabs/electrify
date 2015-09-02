/*
  ==============================================================================

    SelectionController.cpp
    Created: 17 Aug 2015 3:15:27pm
    Author:  Kyle Fleming

  ==============================================================================
 */

#include "SelectionController.h"

#include "Selectable.h"
#include "SelectionContainer.h"

SelectionController::SelectionController(SelectionContainer* selectionContainer)
: selectionContainer(selectionContainer)
{
}

bool SelectionController::hasSelection() const
{
    return selectedItems.size() >= 1;
}

void SelectionController::select(Selectable* item)
{
    item->selected << true;
    selectedItems.push_back(item);
}

void SelectionController::toggleSelected(Selectable* item, bool enableMulti)
{
    if (!enableMulti && selectedItems.size() >= 1) {
        deselectAll();
        select(item);
        return;
    }
    for (auto iter = selectedItems.begin(); iter != selectedItems.end(); ++iter) {
        if (*iter == item) {
            item->selected << false;
            selectedItems.erase(iter);
            return;
        }
    }
    select(item);
}

void SelectionController::setSelected(const vector<Selectable*>& items)
{
    deselectAll();
    selectedItems.assign(items.begin(), items.end());
    for (auto selectedItem : selectedItems) {
        selectedItem->selected << true;
    }
}

void SelectionController::deselect(Selectable* item)
{
    for (auto iter = selectedItems.begin(); iter != selectedItems.end(); ++iter) {
        if (*iter == item) {
            item->selected << false;
            selectedItems.erase(iter);
            return;
        }
    }
}

void SelectionController::deselectAll()
{
    for (auto selectedItem : selectedItems) {
        selectedItem->selected << false;
    }
    selectedItems.clear();
}

void SelectionController::deleteSelected()
{
    for (auto selectedItem : selectedItems) {
        selectedItem->selected << false;
        selectedItem->deleteSelectable();    }
    selectedItems.clear();
}

bool SelectionController::keyPressed(const KeyPress& key, Component* originatingComponent)
{
    if (key == juce::KeyPress::deleteKey || key == juce::KeyPress::backspaceKey) {
        if (hasSelection()) {
            deleteSelected();
        }
    }
    return false;
}
