/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#include <assert.h>
#include <math.h>
#include "applicationTest.h"

#define USER 2

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
	int productObj;

	// create the shopping chart
	Basket b1;

	// create product (to be done by future store class)
	if (USER == 1)
	{
		Product p1("2 book at 12.49", Product::taxCategory::book);
		Product p2("1 music CD at 14.99", Product::taxCategory::genericProduct);
		Product p3("1 chocolate bar at 0.85", Product::taxCategory::food);
		app_pt->KeepProduct(&p1,&b1);
		app_pt->KeepProduct(&p2,&b1);
		app_pt->KeepProduct(&p3,&b1);
		productObj = 3;
	}
	else if (USER == 2)
	{
		Product p1("1 imported box of chocolates at 10.00", Product::taxCategory::food);
		Product p2("1 imported bottle of perfume at 47.50", Product::taxCategory::genericProduct);
		app_pt->KeepProduct(&p1,&b1);
		app_pt->KeepProduct(&p2,&b1);
		productObj = 2;
	}
	else if (USER == 3)
	{
		Product p1("1 imported bottle of perfume at 27.99", Product::taxCategory::genericProduct);
		Product p2("1 bottle of perfume at 18.99", Product::taxCategory::genericProduct);
		Product p3("1 packet of headache pills at 9.75", Product::taxCategory::medicine);
		Product p4("3 box of imported chocolates at 11.25", Product::taxCategory::food);
		app_pt->KeepProduct(&p1,&b1);
		app_pt->KeepProduct(&p2,&b1);
		app_pt->KeepProduct(&p3,&b1);
		app_pt->KeepProduct(&p4,&b1);
		productObj = 4;
	}
	else
	{
		// other user
		Product p1("1 imported bottle of perfume at 27.99", Product::taxCategory::genericProduct);
		Product p2("1 bottle of perfume at 18.99", Product::taxCategory::genericProduct);
		Product p3("1 packet of headache pills at 9.75", Product::taxCategory::medicine);
		Product p4("3 box of imported chocolates at 11.25", Product::taxCategory::food);
		app_pt->KeepProduct(&p1,&b1);
		app_pt->KeepProduct(&p2,&b1);
		app_pt->KeepProduct(&p3,&b1);
		app_pt->KeepProduct(&p4,&b1);
		productObj = 4;
	}

	float totalPrice = 0.0;

	// UTest 1: check "Product" object has been correctly added in the basket
	assert (b1.GetBasketSize() == productObj);

	for (int i = 0; i < b1.GetBasketSize(); i++)
	{
		Product * p = b1.GetProduct(i);

		// UTest 2: check if all imported product are correctly marked
		if ((p->GetName().find("imported") != std::string::npos))
		{
			assert(b1.GetProduct(i)->GetIsImported() == true);
		}
		else
		{
			assert(p->GetIsImported() == false);
		}

		// UTest 3: check taxes calculation

		// price check
		assert(p->GetPrice() > 0.0);

		// test taxes taxes
		float taxPercentage_x100 = 0.0;

		if (!p->GetIsBasicSalesTaxed() && !p->GetIsImported())
		{
			// no taxes
			taxPercentage_x100 = 0.0;
		}
		else if (p->GetIsBasicSalesTaxed() && p->GetIsImported())
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

		// consider the number of that product
		testTax *= p->GetProductNumber();

		// compare with product tax field
		assert( ( int (p->GetTaxes()*100) == int (testTax*100) ));

		for (int j = 0; j < p->GetProductNumber(); j++)
		{
			totalPrice += p->GetPrice();
		}
	}

	// UTest4: Receipt test
	ReceiptGenerator * p_receipt = new ReceiptGenerator(&b1);
	p_receipt->CalculateReceipt();

	// receipt amount
	assert(p_receipt->GetTotal() >= 0);

	//negative taxes are not allowed
	assert(p_receipt->GetTotalSalesTaxes() >= 0);

	// the receipt total minus the taxes should be equal the sum of products's prices
	assert( (int) (totalPrice + p_receipt->GetTotalSalesTaxes())*100 ==  (int) p_receipt->GetTotal()*100);

	p_receipt->PrintReceipt();

	delete p_receipt;
}

