/*******************************************************************************
	File        : Medicine.cpp
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Medicine class implementation:
				  Medicine specific product class
 *******************************************************************************/

// include
#include "Medicine.h"

// Constructor
Medicine::Medicine(string name, int num, float price):
Product(name, num, price)
{
	isBasicSalesTaxed = false;
}

// Destructor .
Medicine::~Medicine()
{

}
