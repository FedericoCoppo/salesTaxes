/*******************************************************************************
	File        : Medicine.cpp
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Medicine class implementation:
				  Medicine specific product class
 *******************************************************************************/

// Include
#include "Medicine.h"

// Constructor
Medicine::Medicine(string name, int num, float price):
GenericProduct(name, num, price)
{
	isBasicSalesTaxed = false;
}

// Destructor
Medicine::~Medicine()
{

}
