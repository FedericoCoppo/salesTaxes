/*******************************************************************************
	File        : GenericProduct.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : GenericProduct class header
*******************************************************************************/

#ifndef GENERICPRODUCT_H_
#define GENERICPRODUCT_H_

// include
#include <string>

using namespace std;

// Class that implement a Store Product
class GenericProduct
{
public:
	GenericProduct(string prodName, int prodNum, float prodPrice);
	virtual ~GenericProduct(void);
	float CalculateTaxes();
	float RoundUpTo05(float num);

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
	string name;
	int productNumber;
	float price;
	float taxedPrice;
	float taxes;
	float taxesPct;
	bool isImported;
	bool taxesAlreadyCalculated;
};

#endif /* GENERICPRODUCT_H_ */
