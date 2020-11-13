/*******************************************************************************
	File        : Basket.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class
*******************************************************************************/

#include "Basket.h"

// Const
Basket::Basket(void)
{

}


// Dest
Basket::~Basket(void)
{

}

// print method with stdout flush
void Basket::AddProductToBasket(Product * pt)
{
   productList.push_back(*pt);
}

Product * Basket::GetProduct (int idx)
{
	if (idx < GetBasketSize())
	{
	    list<Product>::iterator it = productList.begin();
	    for(int i=0; i< idx; i++)
	    {
	        ++it;
	    }
	    return &(*it);
	}
	else
	{
		return NULL;
	}
}
