/*
  ==============================================================================

    Selectable.hpp.h
    Created: 17 Aug 2015 4:41:43pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "Selectable.h"

#include "SelectionController.h"
#include "SelectionContainer.h"

Selectable::Selectable(SelectionController* selectionController)
: selectionController(selectionController)
{
}

Selectable::Selectable(SelectionContainer* selectionContainer)
: selectionController(&selectionContainer->selectionController)
{
}

void Selectable::setSelected(bool selected)
{
    selectionController->toggleSelected(this);
}

void Selectable::deleteSelectable()
{
    assert(false); // Method stub
}
