/*******************************************************************************
	File        : Tax.cpp
	Date        : 18/11/2020
	Author      : Federico Coppo
	Description : Tax class
				  it represent the product tax
*******************************************************************************/

// Include
#include <Math.h>
#include "Tax.h"
#include "GenericProduct.h"

// Static attribute
const float Tax::importedTaxPercentage = 0.05;
const float  Tax::basedSalesTaxPercentage = 0.10;

// Constructor
Tax::Tax()
{
	tax = 0;
	taxPct = 0;
	isTaxesCalculated = false;
}

// Destructor
Tax::~Tax(void)
{

}

// Tax calculator for the product
void Tax::CalculateTaxes(GenericProduct * p)
{
	if (!isTaxesCalculated)
	{
		isTaxesCalculated = true;

		if (p->GetIsBasicSalesTaxed())
		{
			taxPct += basedSalesTaxPercentage;
		}

		if (p->GetIsImported())
		{
			taxPct += importedTaxPercentage;
		}

		// Consider the number of items
		for (int i = 0; i < p->GetQuantity(); i++ )
		{
			// Round up to the nearest 0.05 the raw tax (%*price)
			tax += RoundUpTo05(taxPct*p->GetPrice());
		}
	}
}

// Utility to round up to 0.05 a decimal float value
float Tax::RoundUpTo05(float num)
{
	return ceil(num*20)/20;
}
