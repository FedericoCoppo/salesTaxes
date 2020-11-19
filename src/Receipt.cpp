/*******************************************************************************
	File        : Receipt.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt class:
				  it calculate and print the receipt
*******************************************************************************/

// Include
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Receipt.h"

// Constructor
Receipt::Receipt(Basket * pt_basket)
{
	p_basket = pt_basket;
	totalSalesTaxes = 0;
	total = 0;
}

// Destructor
Receipt::~Receipt(void)
{

}

// Calculate total cost and cumulative taxes
void Receipt::CalculateReceipt(void)
{
	if (p_basket)
	{
		for (int i = 0; i < p_basket->GetBasketSize(); i++)
		{
			totalSalesTaxes += p_basket->GetProduct(i)->GetTaxesValue();
			total += p_basket->GetProduct(i)->GetPriceTaxed();
		}
	}
}

// Print the receipt
void Receipt::PrintReceipt ()
{
	if (p_basket)
	{
		int maxSize = p_basket->GetBasketSize();
		std::stringstream streamTotalTaxes;
		streamTotalTaxes << std::fixed << std::setprecision(2) << totalSalesTaxes;
		std::stringstream streamTotal;
		streamTotal << std::fixed << std::setprecision(2) << total;

		for (int i = 0; i < maxSize; i++)
		{
			// Product number
			std::stringstream streamNumberOfProduct;
			streamNumberOfProduct << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetQuantity();
			printString(streamNumberOfProduct.str() + " ");

			// Product name
			printString(p_basket->GetProduct(i)->GetName() + ": ");

			// Product price
			std::stringstream streamTaxedPrice;
			streamTaxedPrice << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetPriceTaxed();
			printLine(streamTaxedPrice.str());
		}

		if (maxSize > 0)
		{
			printString("Sales Taxes: ");
			printLine(streamTotalTaxes.str());

			printString("Total: ");
			printLine(streamTotal.str());
		}
		else
		{
			printLine("Empty basket!");
		}
	}
}

// Print a line with standard output flush for string
void Receipt::printLine(string s)
{
	std::cout << s + "\n";
	fflush(stdout);
}
// Print a string with standard output flush for string
void Receipt::printString(string s)
{
	std::cout << s;
	fflush(stdout);
}
