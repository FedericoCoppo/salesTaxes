/*******************************************************************************
	File        : ShoppingSheetList.cpp
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : Shopping Sheet List class:
				  metaphorically it represents the shopping paper list
*******************************************************************************/

#include "ShoppingSheetList.h"

// Constructor
ShoppingSheetList::ShoppingSheetList()
{

}

// Destructor
ShoppingSheetList::~ShoppingSheetList(void)
{
	// Clear the list if not already done by user
	noteList.clear();
}

// Insert a new product note in the shopping list
void ShoppingSheetList::AddShoppingNoteToList(ShoppingNote * pt)
{
	if (pt)
	{
		noteList.push_back(pt);
	}
}

// Remove all note from shopping list
void ShoppingSheetList::ClearNoteFromShoppingList()
{
	noteList.clear();
}


// Get Note from the shopping list
ShoppingNote * ShoppingSheetList::GetShoppingNote(int idx)
{
	if (idx < GetShoppingNoteListSize())
	{
	    list<ShoppingNote *>::iterator it = noteList.begin();

	    for(int i=0; i< idx; i++)
	    {
	        ++it;
	    }

	    return *it;
	}
	else
	{
		return NULL;
	}
}
