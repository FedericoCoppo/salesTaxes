/*******************************************************************************
	File        : ShoppingNote.h
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : ShoppingNote class header
*******************************************************************************/

#ifndef SHOPPINGNOTE_H_
#define SHOPPINGNOTE_H_

// include
#include <string>

using namespace std;

// Class that implement product description annotation
class ShoppingNote
{
public:

	// product type for basics sales tax category
	typedef enum
	{
		book,
		food,
		medicine,
		genericProduct

	} productCategory;

	ShoppingNote(string noteStr, productCategory productCat);
	virtual ~ShoppingNote(void);

	// Getter
	string GetShoppingNoteString() { return note; }
	productCategory GetShoppingNoteCategory() { return category; }

private:

	// product info input string
	string note;

	// product category
	productCategory category;
};

#endif /* SHOPPINGNOTE_H_ */
