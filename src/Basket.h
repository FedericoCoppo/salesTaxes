/*******************************************************************************
	File        : Basket.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class header
*******************************************************************************/

#ifndef BASKET_H_
#define BASKET_H_

using namespace std;

// include
#include <list>
#include "GenericProduct.h"

// Class that implement a shopping cart
class Basket
{
public:
	Basket(const char * p_name);
	virtual ~Basket(void);
	void AddProductToBasket(GenericProduct * pt);

	// Getter
	int GetBasketSize(){ return productList.size(); }
	GenericProduct * GetProduct (int idx);
	const char * GetName() { return pt_name; }
private:
	list <GenericProduct> productList;
	const char * pt_name;
};



#endif /* BASKET_H_ */
