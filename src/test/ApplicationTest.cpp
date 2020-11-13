/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#include <assert.h>
#include "applicationTest.h"

// Const
ApplicationTest::ApplicationTest(void)
{
	app_pt = new Application();
}

// Dest
ApplicationTest::~ApplicationTest(void)
{
	if (app_pt != NULL)
	{
		delete app_pt;
		app_pt = NULL;
	}
}

// Main test routine for application class
void ApplicationTest::Test(void)
{
	// create product (to be done by future store class)
	Product p1("chocolates");
	Product p2("dog");
	Product p3("imported chocolates");


	// create the shopping chart
	Basket b1;

	/*
	app_pt->ChooseProduct(&p1,&b1);
	app_pt->ChooseProduct(&p2,&b1);
	app_pt->ChooseProduct(&p3,&b1);
	*/

	// UTest 1: check product has been correctly added in the basket
	assert (b1.GetBasketSize() == 3);

}

