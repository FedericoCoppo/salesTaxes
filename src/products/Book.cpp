/*******************************************************************************
	File        : Book.cpp
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Book class implementation:
				  book specific product class
 *******************************************************************************/

// include
#include "Book.h"

// Constructor
Book::Book(string name, int num, float price):
GenericProduct(name, num, price)
{
	isBasicSalesTaxed = false;
}

// Destructor .
Book::~Book()
{

}
