/*******************************************************************************
	File        : TestApplication.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#ifndef TEST_APPLICATIONTEST_H_
#define TEST_APPLICATIONTEST_H_

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

private:
	void hardCodedInputCreation();
	void testDataStruct();
	void testCalculatedTaxeValues();
	void testReceiptTaxeValues();

	Application * app_pt;
	ShoppingNote * p_shopNote;
	Basket * p_basket;

	ShoppingSheetList shopSheetList_1;
};

#endif /* TEST_APPLICATIONTEST_H_ */
