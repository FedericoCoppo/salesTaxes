/*******************************************************************************
	File        : Basket.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Basket class:
				  it represents a shopping card ready for receipt
*******************************************************************************/

#include "Basket.h"

// Constructor
Basket::Basket(const char * p_name)
{
	pt_name = p_name;
}

// Destructor
Basket::~Basket(void)
{
	// In case forgotten by user...
	RemoveAllProductFromBasket();
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
void Basket::RemoveAllProductFromBasket()
{
	int max = GetBasketSize();
	for (int i = 0; i < max; i++)
	{
		GenericProduct * p_prod = GetProduct(i);

		if (p_prod)
		{
			delete p_prod;
		}
	}

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
