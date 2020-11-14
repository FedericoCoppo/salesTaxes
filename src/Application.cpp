/*******************************************************************************
	File        : Application.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application class header
*******************************************************************************/

// include
#include "Application.h"

// Const.
Application::Application(void)
{

}

// Dest.
Application::~Application(void)
{

}

void Application::KeepProduct(Product * p_product, Basket * p_basket)
{
	p_basket->AddProductToBasket(p_product);
}

// Print method with standard output flush for char *
void Application::PrintLine(const char * pt)
{
	string s = pt;
	std::cout << s + "\n";
	fflush(stdout);
}

// // Print method with standard output flush for string
void Application::PrintString(string s)
{
	std::cout << s + "\n";
	fflush(stdout);
}
