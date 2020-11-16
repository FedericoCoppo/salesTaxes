/*******************************************************************************
	File        : Application.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application class header:
				  it represent the user that convert the shopping notes into
				  products and fill the basket
*******************************************************************************/

// include
#include <sstream>

#include "Application.h"

// Static attribute
const int Application::ProductNumberMax = 1000;
const int Application::ProducNameCharacterMin = 3;

// Constructor
Application::Application(void)
{
	discardedNotesCnt = 0;
}

// Destructor
Application::~Application(void)
{

}

// Fill the buffer with products converted from shopping list
void Application::FillBasketFromShoppingList(ShoppingSheetList *p_shopList, Basket * p_basket)
{
	ShoppingNote * p_shopNoteTmp;
	GenericProduct * p_productTmp;
	int ShopListSize = 0;

	if (p_shopList)
	{
		ShopListSize = p_shopList->GetShoppingNoteListSize();
	}

	// for each  notes
	for (int i = 0; i < ShopListSize; i++)
	{
		p_shopNoteTmp = p_shopList->GetShoppingNote(i);

		if (p_shopNoteTmp)
		{
			// validate the note before creating a new product
			string prodName;
			int prodNum = 0;
			float prodPrice = 0.0;

			// validate the note
			if (validateShoppingNote(p_shopNoteTmp->GetShoppingNoteString(), &prodNum, &prodName, &prodPrice))
			{
				// convert the note into product
				switch (p_shopNoteTmp->GetShoppingNoteCategory())
				{
				case ShoppingNote::productCategory::book:
					p_productTmp = new Book(prodName, prodNum, prodPrice);
					break;
				case ShoppingNote::productCategory::food:
					p_productTmp = new Food(prodName, prodNum, prodPrice);
					break;
				case ShoppingNote::productCategory::medicine:
					p_productTmp = new Medicine(prodName, prodNum, prodPrice);
					break;
				case ShoppingNote::productCategory::genericProduct:
					p_productTmp = new GenericProduct(prodName, prodNum, prodPrice);
					break;
				}

				// add the product to basket
				if (p_basket)
				{
					p_basket->AddProductToBasket(p_productTmp);
				}
			}
			else
			{
				discardedNotesCnt++;
			}
		}
	}
}

// Clear the basket from product
void Application::ClearBasketFromAllProduct(Basket * p_basket)
{
	if (p_basket)
	{
		p_basket->RemoveAllProductFromBasket();
	}
}

//  Validate the shopping list note
bool Application::validateShoppingNote(string s, int * p_number, string * p_name, float * p_price)
{
	bool res = true;

	// Check the number number
	int num;
	string numStr = s.substr(0, s.find(" "));
	stringstream ssNum(numStr);
	ssNum >> num;
	*p_number = num;

	// avoid too big or negative input value
	if ( (num >= Application::ProductNumberMax) || (num <= 0) )
	{
		res = false;
	}
	else
	{
		// check the name
		s = s.erase(0, numStr.length() + 1);
		string nameStr = s.substr(0, s.find(" at "));

		// avoid too little input name
		if (nameStr.length() < Application::ProducNameCharacterMin)
		{
			res = false;
		}
		else
		{
			*p_name = nameStr;

			// get the product price
			string priceStr = s.erase(0, nameStr.length() + 4);

			// avoid wrong format price input
			try
			{
				*p_price = std::stof(priceStr);
			}
			catch (const std::invalid_argument& ia)
			{
				std::cerr << "Invalid argument: " << ia.what() << '\n';
				res = false;
			}
		}
	}

	return res;
}

// Print method with standard output flush for char *
void Application::PrintLine(const char * pt)
{
	string s = pt;
	std::cout << s + "\n";
	fflush(stdout);
}

// Print method with standard output flush for string
void Application::PrintString(string s)
{
	std::cout << s + "\n";
	fflush(stdout);
}
