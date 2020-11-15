/*******************************************************************************
	File        : Basket.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class:
				  it represents a shopping card ready for receipt
*******************************************************************************/

#include "Basket.h"

// Const.
Basket::Basket(const char * p_name)
{
	pt_name = p_name;
}

// Dest.
Basket::~Basket(void)
{
	productList.clear();
}

// Add a new product to shopping basket
void Basket::AddProductToBasket(GenericProduct * pt)
{
	if (pt)
	{
		productList.push_back(*pt);
	}
}

// Get product at specific index
GenericProduct * Basket::GetProduct (int idx)
{
	if (idx < GetBasketSize())
	{
	    list<GenericProduct>::iterator it = productList.begin();
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
