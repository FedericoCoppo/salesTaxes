/*******************************************************************************
	File        : Application.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application header
 *******************************************************************************/

#ifndef APPLICATION_H_
#define APPLICATION_H_

// include
#include <iostream>
#include <string>

#include "GenericProduct.h"
#include "Food.h"
#include "Book.h"
#include "Medicine.h"
#include "Basket.h"
#include "Receipt.h"
#include "ShoppingSheetList.h"

using namespace std;

// Class that implement the Application
class Application
{
public:
	Application(void);
	virtual ~Application(void);
	void FillBasketFromShoppingList(ShoppingSheetList *p_shopList, Basket * p_basket);
	void ClearBasketFromAllProduct(Basket * p_basket);
	void PrintLine(const char * pt);
	void PrintString(string s);

private:
	bool validateShoppingNote(string s, int * p_number, string * p_name, float * p_price);

	// maximum input value allowed
	static const int ProductNumberMax;
	static const int ProducNameCharacterMin;
};

#endif /* APPLICATION_H_ */
