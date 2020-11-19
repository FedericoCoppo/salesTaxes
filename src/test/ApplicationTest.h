/*******************************************************************************
	File        : TestApplication.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : TestApplication header
*******************************************************************************/

#ifndef TEST_APPLICATIONTEST_H_
#define TEST_APPLICATIONTEST_H_

// Include
#include "Application.h"
#include "ShoppingNote.h"
#include "ShoppingSheetList.h"
#include "InputProvider.h"

// Test application class
class ApplicationTest
{
public:
	ApplicationTest(void);
	virtual ~ApplicationTest(void);
	void Test(void);

private:
	void testProduct();
	void testShoppingSheetList();
	void testDataStructCoherence();
	void testCalculatedTaxesValues();
	void testReceipt();
	void testDifferentInputSource(int testCnt);
	void configureTest(int testCnt);
	void clearApplicationTest();

	Application * p_app;
	Basket * p_basket;
	ShoppingSheetList * p_shopSheetList;
	InputProvider * p_input;

	static const unsigned char inputSourceMax;
};

#endif /* TEST_APPLICATIONTEST_H_ */
