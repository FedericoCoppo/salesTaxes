/*******************************************************************************
	File        : Food.cpp
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Food class implementation:
				  food specific product class
*******************************************************************************/

// Include
#include "Food.h"

// Constructor
Food::Food(string name, int num, float price):
	GenericProduct(name, num, price)
{
	isBasicSalesTaxed = false;
}

// Destructor
Food::~Food()
{

}
