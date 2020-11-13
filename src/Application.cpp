/*******************************************************************************
	File        : Application.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application routine
*******************************************************************************/

// include
#include "Application.h"


// Const
Application::Application(void)
{

}


// Dest
Application::~Application(void)
{

}

void Application::ChooseProduct(Product * p_product, Basket * p_basket)
{
	p_basket->AddProductToBasket(p_product);
}

// print method with stdout flush
void Application::PrintLine(const char * pt)
{
	string s = pt;
	std::cout << s + "\n";
	fflush(stdout);
}

// print method with stdout flush
void Application::PrintString(string s)
{
	std::cout << s + "\n";
	fflush(stdout);
}
