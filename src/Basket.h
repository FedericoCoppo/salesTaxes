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
#include "Product.h"

// Class that implement a shopping cart
class Basket
{
public:
	Basket();
	virtual ~Basket(void);
	void AddProductToBasket(Product * pt);

	// Getter
	int GetBasketSize(){ return productList.size(); }
	Product * GetProduct (int idx);

private:
	list <Product> productList;
};



#endif /* BASKET_H_ */
