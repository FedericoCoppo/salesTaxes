/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#include <assert.h>
#include <math.h>
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

	app_pt->ChooseProduct(&p1,&b1);
	app_pt->ChooseProduct(&p2,&b1);
	app_pt->ChooseProduct(&p3,&b1);

	float totalPrice = 0.0;


	// UTest 1: check product has been correctly added in the basket
	assert (b1.GetBasketSize() == 3);

	for (int i = 0; i < b1.GetBasketSize(); i++)
	{
		Product * p = b1.GetProduct(i);

		// UTest 2: check if all imported product are correctly marked
		if ((p->GetName().find("imported") == 0))
		{
			assert(b1.GetProduct(i)->GetImported() == true);
		}
		else
		{
			assert(p->GetImported() == false);
		}

		// UTest 3: check taxes calculation

		// price check
		assert(p->GetPrice() > 0.0);

		// test taxes taxes
		float taxPercentage_x100 = 0.0;

		if (!p->GetIsBasicSalesTaxed() && !p->GetImported())
		{
			// no taxes
			taxPercentage_x100 = 0.0;
		}
		else if (p->GetIsBasicSalesTaxed() && p->GetImported())
		{
			// both taxes 10% and 5%
			taxPercentage_x100 = 0.15;
		}
		else if (p->GetIsBasicSalesTaxed())
		{
			// basic tax
			taxPercentage_x100 = 0.10;
		}
		else
		{
			// import tax
			taxPercentage_x100 = 0.05;
		}

		// calculate the tax
		float testTax = p->GetPrice()*taxPercentage_x100;

		// round up to the nearest 0.05
		testTax = ceil(testTax*20)*0.05;

		// compare with product tax field
		assert( ( int (p->GetTaxes()*100) == int (testTax*100) ));

		totalPrice += p->GetPrice();
	}

	// UTest4: Receipt test
	ReceiptGenerator * p_receipt = new ReceiptGenerator(&b1);

	// receipt should be on amount
	assert(p_receipt->GetTotal() > 0);

	//negative taxes are not allowed
	assert(p_receipt->GetTotalSalesTaxes() >= 0);

	// the receipt total minus the taxes should be equal the sum of products's prices
	assert( (int) (totalPrice + p_receipt->GetTotalSalesTaxes())*100 ==  (int) p_receipt->GetTotal()*100);

	delete p_receipt;
}

