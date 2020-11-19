/*******************************************************************************
	File        : Tax.h
	Date        : 18/11/2020
	Author      : Federico Coppo
	Description : Tax class header
*******************************************************************************/

#ifndef TAX_H_
#define TAX_H_

class GenericProduct;

// Class that implement the tax
class Tax
{
public:
	Tax();
	virtual ~Tax();
	void CalculateTaxes(GenericProduct * p);
	float RoundUpTo05(float num);

	// Getter
	float GetTax() { return tax; }

private:
	float tax;
	float taxPct;
	bool isTaxesCalculated;

	// Taxes percentage
	static const float importedTaxPercentage;
	static const float basedSalesTaxPercentage;
};

#endif /* TAX_H_ */
