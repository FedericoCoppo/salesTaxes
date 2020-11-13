/*******************************************************************************
	File        : Product.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Product class
*******************************************************************************/

#include "Product.h"

// Const
Product::Product(const char * name)
{
	p_name = name;
	price = 0.0;
	taxes = 0.0;
	imported = false;
	isBasicSalesTaxed = false;
}

// Dest
Product::~Product(void)
{
	price = 0.0;
	taxes = 0.0;
	imported = false;
	isBasicSalesTaxed = false;
}

float Product::calculateTaxes()
{
	return 0.0;
}



