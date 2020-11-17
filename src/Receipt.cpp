/*******************************************************************************
	File        : Receipt.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt generator class:
				  it calculate and print the receipt
*******************************************************************************/

// include
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
	p_basket = NULL;
}

// Calculate total cost and cumulative taxes
void Receipt::CalculateReceipt(void)
{
	if (p_basket)
	{
		for (int i = 0; i < p_basket->GetBasketSize(); i++)
		{
			totalSalesTaxes += p_basket->GetProduct(i)->GetTaxes();
			total += p_basket->GetProduct(i)->GetTaxedPrice();
		}
	}
}

// Print the receipt
void Receipt::PrintReceipt ()
{
	if (p_basket)
	{
		printLine(p_basket->GetName());

		std::stringstream streamTotalTaxes;
		streamTotalTaxes << std::fixed << std::setprecision(2) << totalSalesTaxes;
		std::stringstream streamTotal;
		streamTotal << std::fixed << std::setprecision(2) << total;

		for (int i = 0; i < p_basket->GetBasketSize(); i++)
		{
			// product number
			std::stringstream streamNumberOfProduct;
			streamNumberOfProduct << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetQuantity();
			printString(streamNumberOfProduct.str() + " ");

			// product name
			printString(p_basket->GetProduct(i)->GetName() + ": ");

			// product price
			std::stringstream streamTaxedPrice;
			streamTaxedPrice << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetTaxedPrice();
			printLine(streamTaxedPrice.str());
		}

		// shopping totale sales taxes
		printString("Sales Taxes: ");
		printLine(streamTotalTaxes.str());

		// shopping total price
		printString("Total: ");
		printLine(streamTotal.str());
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
