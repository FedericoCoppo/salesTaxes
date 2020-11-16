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

// Test application class
class ApplicationTest
{
public:
	ApplicationTest(void);
	virtual ~ApplicationTest(void);
	void Test(void);
	void ClearShoppingSheet(ShoppingSheetList * p_list);

private:
	void hardCodedInputCreation();
	void testProduct();
	void testShoppingSheetList();
	void testDataStruct();
	void testCalculatedTaxesValues();
	void testReceipt();
	void hardCodedWrongInputCreated();
	void generateInput(void);

	Application * app_pt;
	ShoppingNote * p_shopNote;
	Basket * p_basket;
	Receipt * p_receipt;

	ShoppingSheetList * p_shopSheetList;
};

#endif /* TEST_APPLICATIONTEST_H_ */
