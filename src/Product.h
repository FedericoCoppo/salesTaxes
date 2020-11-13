/*******************************************************************************
	File        : Product.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Product header
*******************************************************************************/

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <string>
using namespace std;

// Class that implement a store Product
class Product
{
public:
	Product(const char * name);
	virtual ~Product(void);

	// Getter
	string GetName() { return (string) p_name;}
	bool GetImported() {return imported;}
	float GetPrice() { return price; }
	float GetTaxes() { return taxes; }
	float GetIsBasicSalesTaxed() { return isBasicSalesTaxed; }


private:
	float calculateTaxes();
	void setTaxes(float t) {taxes = t;}

	const char * p_name;
	float price;
	float taxes;
	bool imported;
	bool isBasicSalesTaxed;

};

#endif /* PRODUCT_H_ */
