/*******************************************************************************
	File        : ShoppingSheetList.h
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : ShoppingSheetList class header
*******************************************************************************/

#ifndef SHOPPINGSHEETLIST_H_
#define SHOPPINGSHEETLIST_H_

// include
#include <string>
#include <list>

#include "ShoppingNote.h"

using namespace std;

// Class to manage list of Notes
class ShoppingSheetList
{
public:
	ShoppingSheetList();
	virtual ~ShoppingSheetList();
	void AddShoppingNoteToList(ShoppingNote * pt);
	void RemoveAllNoteFromShoppingList();

	// Getter
	ShoppingNote * GetShoppingNote(int idx);
	int GetShoppingNoteListSize() { return noteList.size(); }

private:
	list <ShoppingNote *> noteList;
};

#endif /* SHOPPINGSHEETLIST_H_ */
