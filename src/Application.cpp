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
#include <string.h>

#include "Application.h"

// Static attribute
const int Application::ProductNumberMax = 1000;
const int Application::ProducNameCharacterMin = 3;

// Constructor
Application::Application(InputProvider::InputSource source, const char * sourcePath, const char * vocabPath)
{
	discardedNotesCnt = 0;
	p_basket = NULL;
	p_receipt = NULL;

	// Create input and link with the application
	p_input = new InputProvider();
	p_shopSheetList = p_input->InputCreate(source, sourcePath, vocabPath);

	// Create Basket
	p_basket = new Basket("USER " + to_string(p_input->GetUser()));

	//  Create Receipt
	p_receipt = new Receipt(p_basket);
}

// Destructor
Application::~Application(void)
{
	if (p_input)
	{
		delete p_input;
		p_input = NULL;
	}

	p_shopSheetList = NULL;

	if (p_basket)
	{
		ClearBasket();
		delete p_basket;
		p_basket = NULL;
	}

	if (p_receipt)
	{
		delete p_receipt;
		p_receipt = NULL;
	}
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

		if (p_shopNoteTmp && p_basket)
		{
			// validate the note before creating a new product
			string prodName;
			int prodNum = 0;
			float prodPrice = 0.0;

			// validate the note, then add the product to basket
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

				p_basket->AddProductToBasket(p_productTmp);
			}
			else
			{
				discardedNotesCnt++;
			}
		}
	}
}

// Clear the basket from product
void Application::ClearBasket()
{
	// remove the product
	if (p_basket)
	{
		int max = p_basket->GetBasketSize();

		for (int i = 0; i < max; i++)
		{
			GenericProduct * p_prod = p_basket->GetProduct(i);

			if (p_prod)
			{
				delete p_prod;
			}
		}
	}

	// clear the list
	p_basket->ClearProductFromBasket();
}

//  Validate the shopping list note
bool Application::validateShoppingNote(string s, int * p_number, string * p_name, float * p_price)
{
	bool res = true;

	// Check the number number
	int num = 0;
	string numStr = s.substr(0, s.find(" "));
	stringstream ssNum(numStr);

	if (isValidPrice(ssNum.str()))
	{
		ssNum >> num;
		*p_number = num;
	}

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

			if (isValidPrice(priceStr))
			{
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

				// avoid considering product with price equal zero
				if ( (res == true) && (*p_price == 0))
				{
					res = false;
				}
			}
			else
			{
				res = false;
			}
		}
	}

	return res;
}

// Routine to check if string is a valid product number
bool Application::isValidProductNumber(const std::string &s)
{
	return( strspn( s.c_str(), "0123456789" ) == s.size() );
}

// Routine to check if string is a number valid for price
bool Application::isValidPrice(const std::string &s)
{
	// "1." are valid for 1.0; ".5" is valid for 0.5
	return( strspn( s.c_str(), ".0123456789" ) == s.size() );
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
