/*******************************************************************************
	File        : GenericProduct.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : GenericProduct class:
				  it represent the store product with all purchase information
*******************************************************************************/

// include
#include <sstream>
#include <iostream>

#include "GenericProduct.h"

// Constructor
GenericProduct::GenericProduct(string prodName, int prodQuantity, float prodPrice)
{
	name = prodName;
	quantity = prodQuantity;
	priceRaw = prodPrice;
	priceTaxed = priceRaw;

	isImported = false;
	isBasicSalesTaxed = true;

	// mark as additional input duty
	if (GetName().find("imported") != std::string::npos)
	{
		isImported = true;
	}
}

// Destructor
GenericProduct::~GenericProduct(void)
{

}

// sales tax calculation routine
float GenericProduct::CalculateTaxes()
{
	productTax.CalculateTaxes(this);
	priceTaxed = priceRaw*quantity + productTax.GetTax();

	return productTax.GetTax();
}


