/*******************************************************************************
	File        : Product.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Product class header
*******************************************************************************/

#ifndef PRODUCT_H_
#define PRODUCT_H_

// include
#include <string>

using namespace std;

// Class that implement a Store Product
class Product
{
public:
	Product(string prodName, int prodNum, float prodPrice);
	virtual ~Product(void);
	float CalculateTaxes();

	// Getter
	string GetName() { return name;}
	bool GetIsImported() {return isImported;}
	float GetPrice() { return price; }
	float GetTaxes() { return taxes; }
	float GetIsBasicSalesTaxed() { return isBasicSalesTaxed; }
	float GetTaxedPrice() { return taxedPrice; }
	int GetProductNumber() { return productNumber; }

protected:
	bool isBasicSalesTaxed = false;

private:
	float roundUpTo05(float num);

	string name;
	int productNumber;
	float price;
	float taxedPrice;
	float taxes;
	float taxesPct;
	bool isImported;
	bool taxesAlreadyCalculated;
};

#endif /* PRODUCT_H_ */
