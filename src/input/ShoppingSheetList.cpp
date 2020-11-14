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
	noteList.clear();
}

// Adds a new product note to the shopping list
void ShoppingSheetList::AddShoppingNoteToList(ShoppingNote * pt)
{
	if (pt)
	{
		noteList.push_back(*pt);
	}
}

// Keep note info from the shopping list
ShoppingNote * ShoppingSheetList::ExtractShoppingNoteFromList(int idx)
{
    list<ShoppingNote>::iterator it = noteList.begin();

    for(int i=0; i< idx; i++)
    {
        ++it;
    }

    return &(*it);
}

