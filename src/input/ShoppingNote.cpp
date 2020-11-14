/*******************************************************************************
	File        : ShoppingNote.cpp
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : Note class:
				  metaphorically a Shopping note is an item of a shopping list
*******************************************************************************/

#include "ShoppingNote.h"

// Const.
ShoppingNote::ShoppingNote(const char * p_note, productCategory productCat)
{
	note = (string) p_note;
	category = productCat;
}

// Dest.
ShoppingNote::~ShoppingNote(void)
{

}

