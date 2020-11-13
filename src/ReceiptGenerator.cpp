/*******************************************************************************
	File        : ReceiptGenerator.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt generator class
*******************************************************************************/

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

	}
}

