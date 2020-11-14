/*******************************************************************************
	File        : Product.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Product class:
				  it represent the store product with all purchase information
*******************************************************************************/

// include
#include <sstream>
#include <iostream>
#include <Math.h>

#include "Product.h"

using namespace std;

// Const.
Product::Product(const char * p_line, taxCategory cat)
{
	inputString = (string) p_line;
	category = cat;

	price = 0.0;
	taxes = 0.0;
	taxesPct = 0.0;
	productNumber = 1;
	isImported = false;
	isBasicSalesTaxed = false;

	if (category == genericProduct)
	{
		isBasicSalesTaxed = true;
		taxesPct = 0.1;
	}

	parseInputLine();
	calculateTaxes();
}

// Dest.
Product::~Product(void)
{
	price = 0.0;
	taxes = 0.0;
	isImported = false;
	isBasicSalesTaxed = false;
}

// line parsing
void Product::parseInputLine (void)
{
	// number of product
	string occurency = inputString.substr(0, inputString.find(" "));
	stringstream ssOccurency(occurency);

	// in case of invalid argument the value is maintained equal zero
	ssOccurency >> productNumber;

	// product name
	inputString = inputString.erase(0, occurency.length() + 1);
	name = inputString.substr(0, inputString.find(" at "));

	// mark as additional input duty
	if (GetName().find("imported") != std::string::npos)
	{
		isImported = true;
		taxesPct += 0.05;
	}

	// product price
	string priceStr = inputString.erase(0, name.length() + 4);

	try
	{
		// stof with invalid argument produce exception
		price = std::stof(priceStr);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << "Invalid argument: " << ia.what() << '\n';
		return;
	}
}

// sales tax calculation routine
float Product::calculateTaxes()
{
	float rawTaxes;

	for (int i = 0; i < productNumber; i++ )
	{
		rawTaxes = taxesPct*price;
		taxes += roundUpTo05(rawTaxes);
	}

	return taxes;
}

float Product::roundUpTo05(float num)
{
	return ceil(num*20)/20;
}


