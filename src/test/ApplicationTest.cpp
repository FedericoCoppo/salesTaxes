/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application
				  it create and test Application
*******************************************************************************/

// include
#include <assert.h>
#include <math.h>
#include <sstream>
#include <string.h>

#include "applicationTest.h"

// static attribute
const unsigned char ApplicationTest::inputSourceMax = 10;

// Constructor
ApplicationTest::ApplicationTest(void)
{
	app_pt = NULL;
	p_basket = NULL;
	p_receipt = NULL;
	p_input = NULL;
	p_shopSheetList = NULL;
}

// Destructor
ApplicationTest::~ApplicationTest(void)
{
	clearApplicationTest();
}

// Clear the application pointers
void ApplicationTest::clearApplicationTest()
{
	// clear the heap
	if (app_pt != NULL)
	{
		delete app_pt;
		app_pt = NULL;
	}

	p_basket = NULL;
	p_receipt = NULL;
	p_input = NULL;
	p_shopSheetList = NULL;
}

// Test different input sources
void ApplicationTest::testDifferentInputSource(int testCnt)
{
	cout << "\nTest " << testCnt << ":\n";

	if (testCnt == 1)
	{
		// Good file input 1
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt", "src/input/categoryVocabulary.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 3);
	}
	else if (testCnt == 2)
	{
		// Good file input 2
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes2.txt", "src/input/categoryVocabulary.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 2);
	}
	else if (testCnt == 3)
	{
		// Good file input 3
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes3.txt", "src/input/categoryVocabulary.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 4);
	}
	else if (testCnt == 4)
	{
		// Good file input 4
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes4.txt", "src/input/categoryVocabulary.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 4);
	}
	else if (testCnt == 5)
	{
		// Hard coded input
		app_pt = new Application();
	}
	else if (testCnt == 6)
	{
		// No file path provided
		app_pt = new Application(InputProvider::InputSource::file);
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 7)
	{
		// No Configuration Vocabulary path provided
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 8)
	{
		// Wrong path for both files
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotesX.txt", "src/input/categoryVocabularyX.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 9)
	{
		// Wrong input notes file only
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotesX.txt", "src/input/categoryVocabulary.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 10)
	{
		// Vocabulary with unknown categories
		app_pt = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt", "src/input/categoryVocabulary2.txt");
		assert (app_pt->GetInputProvider()->GetMapProductCategorySize() == 3);
		assert (app_pt->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 3);
	}
}

// Check that all product object has been correctly added in the basket
void ApplicationTest::testDataStruct()
{
	int productObj = p_shopSheetList->GetShoppingNoteListSize() - app_pt->GetDiscardedNotesCnt();
	assert (p_basket->GetBasketSize() == productObj);
}

// Test product taxes calculation
void ApplicationTest::testCalculatedTaxesValues()
{
	for (int i = 0; i < p_basket->GetBasketSize(); i++)
	{
		GenericProduct * p = p_basket->GetProduct(i);
		p->CalculateTaxes();

		// test for multiple taxes calculation on same product
		p->CalculateTaxes();

		// Check if imported products are marked (like in the unit test but here the product come from basket)
		if ((p->GetName().find("imported") != std::string::npos))
		{
			assert(p_basket->GetProduct(i)->GetIsImported() == true);
		}
		else
		{
			assert(p->GetIsImported() == false);
		}

		// Check taxes calculation value
		assert(p->GetPrice() > 0.0);

		// test taxes
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
		testTax *= p->GetQuantity();

		// compare test calculated with the specific product tax field calculated
		assert( ( int (p->GetTaxesValue()*100) == int (testTax*100) ));
	}
}

// Test the Receipt calculation
void ApplicationTest::testReceipt()
{
	float totalPrice = 0.0;

	for (int i = 0; i < p_basket->GetBasketSize(); i++)
	{
		GenericProduct * p = p_basket->GetProduct(i);
		for (int j = 0; j < p->GetQuantity(); j++)
		{
			totalPrice += p->GetPrice();
		}
	}

	// Receipt test
	p_receipt->CalculateReceipt();

	// test receipt amount
	assert(p_receipt->GetTotal() >= 0);

	// negative taxes are not allowed
	assert(p_receipt->GetTotalSalesTaxes() >= 0);

	// consistently test: the receipt total minus the taxes should be equal the sum of products's prices
	assert( (int) (totalPrice + p_receipt->GetTotalSalesTaxes())*100 ==  (int) p_receipt->GetTotal()*100);

	// print the output
	p_receipt->PrintReceipt();
}

// Test Product class
void ApplicationTest::testProduct(void)
{
	// unit test on product
	GenericProduct * p_testProd = NULL;
	GenericProduct * p_testFood = NULL;

	// create a product
	float initPrice = 5.57;
	float prodNum = 4;
	p_testProd = new GenericProduct("testProduct imported", prodNum, initPrice);
	p_testFood = new Food("testProduct", prodNum, initPrice);

	// check the attribute
	assert ( p_testProd->GetQuantity() == prodNum);
	assert ( p_testProd->GetPrice( ) == initPrice);

	// test 1 round utility
	float roundValue = p_testProd->GetTax()->RoundUpTo05(0.16);
	stringstream roundValues1_ss;
	roundValues1_ss << roundValue;
	const char * t1 = roundValues1_ss.str().c_str();
	assert ( strcmp(t1, "0.2") == 0);

	// test 2 round utility
	roundValue = p_testProd->GetTax()->RoundUpTo05(0.12);
	stringstream roundValues2_ss;
	roundValues2_ss << roundValue;
	const char * t2 = roundValues2_ss.str().c_str();
	assert ( strcmp(t2, "0.15") == 0);

	// test the correct taxes category
	assert(p_testProd->GetIsBasicSalesTaxed() == true);
	assert(p_testFood->GetIsBasicSalesTaxed() == false);

	// test for imported category
	assert(p_testProd->GetIsImported() == true);
	assert(p_testFood->GetIsImported() == false);

	delete p_testProd;
	delete p_testFood;
}

// Test the Shopping sheet list class
void ApplicationTest::testShoppingSheetList()
{
	ShoppingSheetList * p_shopSheetList = new ShoppingSheetList();
	ShoppingNote * p_note1 = new ShoppingNote("1 imported pen at 5.49", ShoppingNote::productCategory::genericProduct);
	ShoppingNote * p_note2 = new ShoppingNote("2 imported pills at 5.49", ShoppingNote::productCategory::medicine);
	p_shopSheetList->AddShoppingNoteToList(p_note1);
	p_shopSheetList->AddShoppingNoteToList(p_note2);

	// Check that notes are pushed inside the list
	assert(p_shopSheetList->GetShoppingNoteListSize() == 2);

	// Free memory
	p_shopSheetList->ClearNoteFromShoppingList();

	// check the list is empty
	assert(p_shopSheetList->GetShoppingNoteListSize() == 0);

	delete p_shopSheetList;
}

// Test configurator
void ApplicationTest::configureTest(int testCnt)
{
	testDifferentInputSource(testCnt);

	// Link with basket and receipt
	p_basket = app_pt->GetBasket();
	p_receipt = app_pt->GetReceipt();

	// Create input and link with the application
	p_input = app_pt->GetInputProvider();
	p_shopSheetList = app_pt->GetInputShoppingSheetList();

	// Fill basket with data input
	app_pt->FillBasketFromShoppingList(p_shopSheetList, p_basket);
}

// Main test routine for application class
void ApplicationTest::Test(void)
{
	// UTest: test the product class
	testProduct();

	// UTest: test shopping list
	testShoppingSheetList();

	for ( int i = 0; i < ApplicationTest::inputSourceMax; i++)
	{
		// configureTest
		configureTest(i + 1);

		// Functional Test
		testDataStruct();
		testCalculatedTaxesValues();
		testReceipt();

		// clear memory
		clearApplicationTest();
	}
}

