/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application
				  it create and test Application
*******************************************************************************/

// Include
#include <assert.h>
#include <math.h>
#include <sstream>
#include <string.h>
#include "applicationTest.h"

// Static attribute
const unsigned char ApplicationTest::inputSourceMax = 10;

// Constructor
ApplicationTest::ApplicationTest(void)
{
	p_app = NULL;
	p_basket = NULL;
	p_input = NULL;
	p_shopSheetList = NULL;
}

// Destructor
ApplicationTest::~ApplicationTest(void)
{
	clearApplicationTest();
}

// Clear memory
void ApplicationTest::clearApplicationTest()
{
	// clear the heap
	if (p_app != NULL)
	{
		delete p_app;
		p_app = NULL;
	}

	p_basket = NULL;
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
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt", "src/input/categoryVocabulary.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 3);
	}
	else if (testCnt == 2)
	{
		// Good file input 2
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes2.txt", "src/input/categoryVocabulary.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 2);
	}
	else if (testCnt == 3)
	{
		// Good file input 3
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes3.txt", "src/input/categoryVocabulary.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 4);
	}
	else if (testCnt == 4)
	{
		// Good file input 4
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes4.txt", "src/input/categoryVocabulary.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 4);
	}
	else if (testCnt == 5)
	{
		// Hard coded input
		p_app = new Application();
	}
	else if (testCnt == 6)
	{
		// No file path provided
		p_app = new Application(InputProvider::InputSource::file);
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 7)
	{
		// No Configuration Vocabulary path provided
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 8)
	{
		// Wrong path for both files
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotesX.txt", "src/input/categoryVocabularyX.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 0);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 9)
	{
		// Wrong input notes file only
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotesX.txt", "src/input/categoryVocabulary.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 13);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 0);
	}
	else if (testCnt == 10)
	{
		// Vocabulary with unknown categories
		p_app = new Application(InputProvider::InputSource::file, "src/input/inputNotes1.txt", "src/input/categoryVocabulary2.txt");
		assert (p_app->GetInputProvider()->GetMapProductCategorySize() == 3);
		assert (p_app->GetInputShoppingSheetList()->GetShoppingNoteListSize() == 3);
	}
}

// Check that all product object has been correctly added in the basket
void ApplicationTest::testDataStruct()
{
	int productObj = p_shopSheetList->GetShoppingNoteListSize() - p_app->GetDiscardedNotesCnt();
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

		// Test taxes
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

		// Calculate the tax
		float testTax = p->GetPrice()*taxPercentage_x100;

		// Round up to the nearest 0.05
		testTax = ceil(testTax*20)*0.05;

		// Consider the number of that product
		testTax *= p->GetQuantity();

		// Compare test calculated with the specific product tax field calculated
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
	p_app->GetReceipt()->CalculateReceipt();

	// Test receipt amount
	assert(p_app->GetReceipt()->GetTotal() >= 0);

	// Negative taxes are not allowed
	assert(p_app->GetReceipt()->GetTotalSalesTaxes() >= 0);

	// Consistently test: the receipt total minus the taxes should be equal the sum of products's prices
	assert( (int) (totalPrice + p_app->GetReceipt()->GetTotalSalesTaxes())*100 ==  (int) p_app->GetReceipt()->GetTotal()*100);

	// Print the output
	p_app->GetReceipt()->PrintReceipt();
}

// Unit test on product class
void ApplicationTest::testProduct(void)
{
	GenericProduct * p_testProd = NULL;
	GenericProduct * p_testFood = NULL;

	// Create a product
	float initPrice = 5.57;
	float prodNum = 4;
	p_testProd = new GenericProduct("testProduct imported", prodNum, initPrice);
	p_testFood = new Food("testProduct", prodNum, initPrice);

	// Check the attribute
	assert ( p_testProd->GetQuantity() == prodNum);
	assert ( p_testProd->GetPrice( ) == initPrice);

	// Test 1 round utility
	float roundValue = p_testProd->GetTax()->RoundUpTo05(0.16);
	stringstream roundValues1_ss;
	roundValues1_ss << roundValue;
	const char * t1 = roundValues1_ss.str().c_str();
	assert ( strcmp(t1, "0.2") == 0);

	// Test 2 round utility
	roundValue = p_testProd->GetTax()->RoundUpTo05(0.12);
	stringstream roundValues2_ss;
	roundValues2_ss << roundValue;
	const char * t2 = roundValues2_ss.str().c_str();
	assert ( strcmp(t2, "0.15") == 0);

	// Test the correct taxes category
	assert(p_testProd->GetIsBasicSalesTaxed() == true);
	assert(p_testFood->GetIsBasicSalesTaxed() == false);

	// Test for imported category
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

	// Check the list is empty
	assert(p_shopSheetList->GetShoppingNoteListSize() == 0);

	delete p_shopSheetList;
}

// Test configurator
void ApplicationTest::configureTest(int testCnt)
{
	testDifferentInputSource(testCnt);

	// Link with basket and receipt
	p_basket = p_app->GetBasket();

	// Create input and link with the application
	p_input = p_app->GetInputProvider();
	p_shopSheetList = p_app->GetInputShoppingSheetList();

	// Fill basket with data input
	p_app->FillBasketFromShoppingList(p_shopSheetList, p_basket);
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
		// ConfigureTest
		configureTest(i + 1);

		// Functional Test
		testDataStruct();
		testCalculatedTaxesValues();
		testReceipt();

		// Clear memory
		clearApplicationTest();
	}
}

