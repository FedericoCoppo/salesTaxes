/*******************************************************************************
	File        : GenericProduct.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : GenericProduct class header
*******************************************************************************/

#ifndef GENERICPRODUCT_H_
#define GENERICPRODUCT_H_

using namespace std;

// Include
#include <string>
#include "Tax.h"

// Class that implement a Store Product
class GenericProduct
{
public:
	GenericProduct(string prodName, int prodQuantity, float prodPrice);
	virtual ~GenericProduct(void);
	float CalculateTaxes();

	// Getter
	string GetName() { return name;}
	int GetQuantity() { return quantity; }
	float GetPrice() { return priceRaw; }
	float GetPriceTaxed() { return priceTaxed; }
	float GetTaxesValue() { return productTax.GetTax(); }
	bool GetIsImported() {return isImported;}
	float GetIsBasicSalesTaxed() { return isBasicSalesTaxed; }
	Tax * GetTax() { return &productTax; }

protected:
	bool isBasicSalesTaxed = false;

private:
	string name;
	int quantity;
	float priceRaw;
	float priceTaxed;
	Tax productTax;
	bool isImported;
};

#endif /* GENERICPRODUCT_H_ */
