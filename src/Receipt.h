/*******************************************************************************
	File        : Receipt.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Receipt class header
*******************************************************************************/

#ifndef RECEIPTGENERATOR_H_
#define RECEIPTGENERATOR_H_

// Include
#include "Basket.h"

// Class that implement a receipt
class Receipt
{
public:
	Receipt(Basket * pt_basket);
	virtual ~Receipt();
	void CalculateReceipt();
	void PrintReceipt();

	// Getter
	float GetTotal() { return total; }
	float GetTotalSalesTaxes() { return totalSalesTaxes; }

private:
	void printLine(string s);
	void printString(string s);

	// Reference basket of this receipt
	Basket * p_basket;

	// Sum of taxes
	float totalSalesTaxes;

	// Final price
	float total;
};

#endif /* RECEIPTGENERATOR_H_ */
