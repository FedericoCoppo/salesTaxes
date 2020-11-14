/*******************************************************************************
	File        : ReceiptGenerator.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt generator class
*******************************************************************************/

// include
#include <iostream>
#include <string>

#include <sstream>
#include <iomanip>


#include "ReceiptGenerator.h"

// Const
ReceiptGenerator::ReceiptGenerator(Basket * pt_basket)
{
	p_basket = pt_basket;
	totalSalesTaxes = 0;
	total = 0;

}

// Dest
ReceiptGenerator::~ReceiptGenerator(void)
{
	p_basket = NULL;
}

// Calculate total and cumulative taxes
void ReceiptGenerator::CalculateReceipt(void)
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


// Print basket's receipt
void ReceiptGenerator::PrintReceipt ()
{
	if (p_basket)
	{

		std::stringstream streamTotalTaxes;
		streamTotalTaxes << std::fixed << std::setprecision(2) << totalSalesTaxes;
		std::stringstream streamTotal;
		streamTotal << std::fixed << std::setprecision(2) << total;

		for (int i = 0; i < p_basket->GetBasketSize(); i++)
		{
			// number
			std::stringstream streamNumberOfProduct;
			streamNumberOfProduct << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetProductNumber();
			printString(streamNumberOfProduct.str() + " ");

			// name
			printString(p_basket->GetProduct(i)->GetName() + ": ");

			// price
			std::stringstream streamTaxedPrice;
			streamTaxedPrice << std::fixed << std::setprecision(2) << p_basket->GetProduct(i)->GetTaxedPrice();
			printLine(streamTaxedPrice.str());
		}

		printString("Sales Taxes: ");
		printLine(streamTotalTaxes.str());
		printString("Total: ");
		printLine(streamTotal.str());
	}
}

// Print a line with standard output flush for string
void ReceiptGenerator::printLine(string s)
{
	std::cout << s + "\n";
	fflush(stdout);
}
// Print a string with standard output flush for string
void ReceiptGenerator::printString(string s)
{
	std::cout << s;
	fflush(stdout);
}
