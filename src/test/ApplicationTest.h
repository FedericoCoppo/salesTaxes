/*******************************************************************************
	File        : TestApplication.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#ifndef TEST_APPLICATIONTEST_H_
#define TEST_APPLICATIONTEST_H_

// include
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
	void testDataStruct();
	void testCalculatedTaxesValues();
	void testReceipt();
	void testDifferentInputSource(int testCnt);
	void configureTest(int testCnt);
	void clearApplicationTest();

	Application * app_pt;
	Basket * p_basket;
	Receipt * p_receipt;
	ShoppingSheetList * p_shopSheetList;
	InputProvider * p_input;

	static const unsigned char inputSourceMax;
};

#endif /* TEST_APPLICATIONTEST_H_ */
