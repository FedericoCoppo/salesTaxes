/*******************************************************************************
	File        : ShoppingNote.cpp
	Date        : 14/11/2020
	Author      : Federico Coppo
	Description : Shopping Note class:
				  metaphorically a shopping note is an item of a shopping list
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

