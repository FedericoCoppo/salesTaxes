/*******************************************************************************
	File        : Receipt.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt generator class header
*******************************************************************************/

#ifndef RECEIPTGENERATOR_H_
#define RECEIPTGENERATOR_H_

#include "Basket.h"

// Class that implement a Receipt
class Receipt
{
public:
	Receipt(Basket * pt_basket);
	virtual ~Receipt();
	void CalculateReceipt();
	void PrintReceipt();
	float GetTotal() { return total; }
	float GetTotalSalesTaxes() { return totalSalesTaxes; }

private:
	void printLine(string s);
	void printString(string s);

	Basket * p_basket;
	float totalSalesTaxes;
	float total;
};

#endif /* RECEIPTGENERATOR_H_ */
