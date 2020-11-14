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
		food,
		book,
		medicine,
		genericProduct

	} productCategory;

	ShoppingNote(const char * p_note, productCategory productCat);
	virtual ~ShoppingNote(void);

private:

	// product input string
	string note;

	// product category
	productCategory category;
};

#endif /* SHOPPINGNOTE_H_ */
