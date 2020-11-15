/*******************************************************************************
	File        : Application.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application class header
*******************************************************************************/

// include
#include <sstream>

#include "Application.h"

// Static attribute
const int Application::ProductNumberMax = 1000;
const int Application::ProducNameCharacterMin = 3;

// Const.
Application::Application(void)
{

}

// Dest.
Application::~Application(void)
{

}

// Move product to basket and remove its description from from sopping list
void Application::FillBasketFromShoppingList(ShoppingSheetList *p_shopList, Basket * p_basket)
{
	ShoppingNote * p_shopNoteTmp;
	Product * p_productTmp;

	for (int i = 0; i < p_shopList->GetShoppingNoteListSize(); i++)
	{
		p_shopNoteTmp = p_shopList->ExtractShoppingNoteFromList(i);

		if (p_shopNoteTmp)
		{
			// validate the note before creating a new product
			string prodName;
			int prodNum = 0;
			float prodPrice = 0.0;

			if (validateShoppingNote(p_shopNoteTmp->GetShoppingNoteString(), &prodNum, &prodName, &prodPrice))
			{
				// create product
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
					p_productTmp = new Product(prodName, prodNum, prodPrice);
					break;
				}

				// add product to basket
				p_basket->AddProductToBasket(p_productTmp);
			}

			// remove your note -> TBD
		}
	}
}

// Application validate shopping list note before creating a new product
bool Application::validateShoppingNote(string s, int * p_number, string * p_name, float * p_price)
{
	bool res = true;

	// Check the number number
	int num;
	string numStr = s.substr(0, s.find(" "));
	stringstream ssNum(numStr);
	ssNum >> num;
	*p_number = num;

	if ( (num >= Application::ProductNumberMax) || (num <= 0) )
	{
		res = false;
	}
	else
	{
		// check the name
		s = s.erase(0, numStr.length() + 1);
		string nameStr = s.substr(0, s.find(" at "));

		if (nameStr.length() < Application::ProducNameCharacterMin)
		{
			res = false;
		}
		else
		{
			*p_name = nameStr;

			// product price
			string priceStr = s.erase(0, nameStr.length() + 4);

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
