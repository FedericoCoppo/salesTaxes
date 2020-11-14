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

	typedef enum
	{
		food,
		book,
		medicine,
		genericProduct

	} taxCategory;

	Product(const char * p_line, taxCategory cat);
	virtual ~Product(void);

	// Getter
	string GetName() { return name;}
	bool GetIsImported() {return isImported;}
	float GetPrice() { return price; }
	float GetTaxes() { return taxes; }
	float GetIsBasicSalesTaxed() { return isBasicSalesTaxed; }
	float GetTaxedPrice() { return taxedPrice; }

private:
	void parseInputLine (void);

	// taxes calculation
	float calculateTaxes();
	float roundUpTo05(float num);

	// taxes value update
	void setTaxes(float t) {taxes = t;}

	string inputString;
	string name;
	int productNumber;
	float price;
	float taxedPrice;
	float taxes;
	float taxesPct;
	bool isImported;
	bool isBasicSalesTaxed;
	taxCategory category;
};

#endif /* PRODUCT_H_ */
