/*******************************************************************************
	File        : ShoppingNote.cpp
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : ShoppingNote class:
				  metaphorically a shopping note is an item of a shopping list
				  that contains product info string and category
*******************************************************************************/

// Include
#include "ShoppingNote.h"

// Constructor
ShoppingNote::ShoppingNote(string noteStr, productCategory productCat)
{
	note = noteStr;
	category = productCat;
}

// Destructor
ShoppingNote::~ShoppingNote(void)
{

}

