/*******************************************************************************
	File        : ReceiptGenerator.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt generator class header
*******************************************************************************/

#ifndef RECEIPTGENERATOR_H_
#define RECEIPTGENERATOR_H_

#include "Basket.h"

// Class that implement a Receipt
class ReceiptGenerator
{
public:
	ReceiptGenerator(Basket * pt_basket);
	virtual ~ReceiptGenerator();
	void CalculateReceipt ();
	void PrintReceipt ();
	float GetTotal() {return total;}
	float GetTotalSalesTaxes() {return totalSalesTaxes;}


private:
	Basket * p_basket;
	float totalSalesTaxes;
	float total;

	void printLine(string s);
	void printString(string s);
};

#endif /* RECEIPTGENERATOR_H_ */
