/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#include <assert.h>
#include <math.h>

#include "applicationTest.h"

#define USER 1

// Const
ApplicationTest::ApplicationTest(void)
{
	app_pt = new Application();
	p_shopNote = NULL;
	p_basket = NULL;
}

// Dest
ApplicationTest::~ApplicationTest(void)
{
	if (app_pt != NULL)
	{
		delete app_pt;
		app_pt = NULL;
	}

	if (p_basket)
	{
		delete p_basket;
		p_basket = NULL;
	}
}

// hard coded input data creation to test application
void ApplicationTest::hardCodedInputCreation()
{
	if (USER == 1)
	{
		p_basket = new Basket("USER 1");
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("2 book at 12.49", ShoppingNote::productCategory::book));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 music CD at 14.99", ShoppingNote::productCategory::genericProduct));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 chocolate bar at 0.85", ShoppingNote::productCategory::food));
	}
	else if (USER == 2)
	{
		p_basket = new Basket("USER 2");
		p_shopNote = new ShoppingNote("1 imported box of chocolates at 10.00", ShoppingNote::productCategory::food);
		shopSheetList_1.AddShoppingNoteToList(p_shopNote);
		p_shopNote = new ShoppingNote("1 imported bottle of perfume at 47.50", ShoppingNote::productCategory::genericProduct);
		shopSheetList_1.AddShoppingNoteToList(p_shopNote);
	}
	else if (USER == 3)
	{
		p_basket = new Basket("USER 3");
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 27.99", ShoppingNote::productCategory::genericProduct));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 bottle of perfume at 18.99", ShoppingNote::productCategory::genericProduct));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 packet of headache pills at 9.75", ShoppingNote::productCategory::medicine));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("3 box of imported chocolates at 11.25", ShoppingNote::productCategory::food));
	}
	else
	{
		p_basket = new Basket("USER 4");
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 imported box of chocolates at 10.50", ShoppingNote::productCategory::genericProduct));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 54.65", ShoppingNote::productCategory::genericProduct));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("2 book at 12.495", ShoppingNote::productCategory::medicine));
		shopSheetList_1.AddShoppingNoteToList(new ShoppingNote("15 box of imported chocolate at 1", ShoppingNote::productCategory::food));
	}
}

// UTest 1: check "Product" object has been correctly added in the basket
void ApplicationTest::testDataStruct()
{
	int productObj = shopSheetList_1.GetShoppingNoteListSize();
	assert (p_basket->GetBasketSize() == productObj);
}

void ApplicationTest::testCalculatedTaxeValues()
{
	for (int i = 0; i < p_basket->GetBasketSize(); i++)
	{
		GenericProduct * p = p_basket->GetProduct(i);
		p->CalculateTaxes();

		// test for multiple taxes calculation on same product
		p->CalculateTaxes();

		// UTest 2: check if all imported product are correctly marked
		if ((p->GetName().find("imported") != std::string::npos))
		{
			assert(p_basket->GetProduct(i)->GetIsImported() == true);
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
			taxPercentage_x100 = 0.0;
		}
		else if (p->GetIsBasicSalesTaxed() && p->GetIsImported())
		{
			taxPercentage_x100 = 0.15;
		}
		else if (p->GetIsBasicSalesTaxed())
		{
			taxPercentage_x100 = 0.10;
		}
		else
		{
			taxPercentage_x100 = 0.05;
		}

		// calculate the tax
		float testTax = p->GetPrice()*taxPercentage_x100;

		// round up to the nearest 0.05
		testTax = ceil(testTax*20)*0.05;

		// consider the number of that product
		testTax *= p->GetProductNumber();

		// compare with specific product tax field
		assert( ( int (p->GetTaxes()*100) == int (testTax*100) ));
	}
}

// test receipt method
void ApplicationTest::testReceiptTaxeValues()
{
	float totalPrice = 0.0;

	for (int i = 0; i < p_basket->GetBasketSize(); i++)
	{
		GenericProduct * p = p_basket->GetProduct(i);
		for (int j = 0; j < p->GetProductNumber(); j++)
		{
			totalPrice += p->GetPrice();
		}
	}

	// UTest4: Receipt test
	Receipt * p_receipt = new Receipt(p_basket);
	p_receipt->CalculateReceipt();

	// receipt amount
	assert(p_receipt->GetTotal() >= 0);

	//negative taxes are not allowed
	assert(p_receipt->GetTotalSalesTaxes() >= 0);

	// the receipt total minus the taxes should be equal the sum of products's prices
	assert( (int) (totalPrice + p_receipt->GetTotalSalesTaxes())*100 ==  (int) p_receipt->GetTotal()*100);

	// print the output
	p_receipt->PrintReceipt();

	delete p_receipt;
}

// Main test routine for application class
void ApplicationTest::Test(void)
{
	// input data creation
	hardCodedInputCreation();

	// from input data to basket
	app_pt->FillBasketFromShoppingList(&shopSheetList_1, p_basket);

	// Test start ...
	testDataStruct();
	testCalculatedTaxeValues();
	testReceiptTaxeValues();

	// Clear shopping list from notes
	shopSheetList_1.RemoveAllNoteFromShoppingList();

	// Clear basket from product
	app_pt->ClearBasketFromAllProduct(p_basket);

	delete p_basket;
	p_basket = NULL;
}

