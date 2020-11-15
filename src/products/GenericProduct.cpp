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
#include <Math.h>

#include "GenericProduct.h"

using namespace std;

// Const.
GenericProduct::GenericProduct(string prodName, int prodNum, float prodPrice)
{
	name = prodName;
	price = prodPrice;
	productNumber = prodNum;
	taxedPrice = price;
	taxes = 0.0;
	taxesPct = 0.0;
	isImported = false;
	isBasicSalesTaxed = true;
	taxesAlreadyCalculated = false;
}

// Dest.
GenericProduct::~GenericProduct(void)
{
	price = 0.0;
	taxes = 0.0;
	isImported = false;
	taxesAlreadyCalculated = false;
}

// sales tax calculation routine
float GenericProduct::CalculateTaxes()
{
	if (!taxesAlreadyCalculated)
	{
		taxesAlreadyCalculated = true;

		float rawTaxes;
		float roundedTaxes;

		// basic sales taxes
		if (isBasicSalesTaxed)
		{
			taxesPct = 0.1;
		}

		// mark as additional input duty
		if (GetName().find("imported") != std::string::npos)
		{
			isImported = true;
			taxesPct += 0.05;
		}

		for (int i = 0; i < productNumber; i++ )
		{
			rawTaxes = taxesPct*price;
			roundedTaxes = roundUpTo05(rawTaxes);
			taxes += roundedTaxes;
		}

		taxedPrice = price*productNumber + taxes;
	}

	return taxes;
}

float GenericProduct::roundUpTo05(float num)
{
	return ceil(num*20)/20;
}


