/*******************************************************************************
	File        : Basket.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class header
				  it is a shopping cart
*******************************************************************************/

#ifndef BASKET_H_
#define BASKET_H_

using namespace std;

// include
#include <list>

#include "GenericProduct.h"

// Class that implement a basket
class Basket
{
public:
	Basket(string nameStr);
	virtual ~Basket(void);
	void AddProductToBasket(GenericProduct * pt);
	void RemoveAllProductFromBasket();

	// Getter
	GenericProduct * GetProduct (int idx);
	int GetBasketSize(){ return productList.size(); }
	string GetName() { return name; }

private:
	list <GenericProduct *> productList;
	string name;
};



#endif /* BASKET_H_ */
