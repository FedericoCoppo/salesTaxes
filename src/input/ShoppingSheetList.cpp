/*******************************************************************************
	File        : ShoppingSheetList.cpp
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : Shopping Sheet List class:
				  metaphorically it represents the shopping paper list
*******************************************************************************/

// include
#include "ShoppingSheetList.h"

// Const.
ShoppingSheetList::ShoppingSheetList()
{

}

// Dest.
ShoppingSheetList::~ShoppingSheetList(void)
{
	// In case forgoten by user...
	RemoveAllNoteFromShoppingList();
}

// Adds a new product note to the shopping list
void ShoppingSheetList::AddShoppingNoteToList(ShoppingNote * pt)
{
	if (pt)
	{
		noteList.push_back(pt);
	}
}

// it remove all product from basket
void ShoppingSheetList::RemoveAllNoteFromShoppingList()
{
	int max = GetShoppingNoteListSize();
	for (int i = 0; i < max; i++)
	{
		ShoppingNote * p_note = GetShoppingNote(i);

		if (p_note)
		{
			delete p_note;
		}
	}

	noteList.clear();
}


// Keep note info from the shopping list
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
