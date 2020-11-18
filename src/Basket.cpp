/*******************************************************************************
	File        : Basket.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class:
				  it represents a shopping card ready for receipt
*******************************************************************************/

// Include
#include "Basket.h"

// Constructor
Basket::Basket(string nameStr)
{
	name = nameStr;
}

// Destructor
Basket::~Basket(void)
{
	// Clear the list if not already done by user
	productList.clear();
}

// Add a new product object to shopping basket
void Basket::AddProductToBasket(GenericProduct * pt)
{
	if (pt)
	{
		productList.push_back(pt);
	}
}

// Remove all product from basket
void Basket::ClearProductFromBasket()
{
	productList.clear();
}

// Get product at specific index
GenericProduct * Basket::GetProduct (int idx)
{
	if (idx < GetBasketSize())
	{
	    list<GenericProduct *>::iterator it = productList.begin();
	    for(int i = 0; i < idx; i++)
	    {
	        ++it;
	    }
	    return *it;
	}
	else
	{
		return NULL;
	}
}
