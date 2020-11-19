/*******************************************************************************
	File        : Application.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application header
				  it represent the user that makes purchases.
 *******************************************************************************/

#ifndef APPLICATION_H_
#define APPLICATION_H_

// Include
#include <iostream>
#include <string>
#include "GenericProduct.h"
#include "Food.h"
#include "Book.h"
#include "Medicine.h"
#include "Basket.h"
#include "Receipt.h"
#include "ShoppingSheetList.h"
#include "InputProvider.h"

// Class that implement the application
class Application
{
public:
	Application(InputProvider::InputSource source = InputProvider::hardCoded, const char * sourcePath = NULL, const char * vocabPath = NULL);
	virtual ~Application(void);
	void FillBasketFromShoppingList(ShoppingSheetList *p_shopList, Basket * p_basket);
	void ClearBasket();
	void PrintLine(const char * pt);
	void PrintString(string s);

	// Getter
	int GetDiscardedNotesCnt() { return discardedNotesCnt;}
	InputProvider * GetInputProvider() { return p_input; }
	ShoppingSheetList * GetInputShoppingSheetList() { return p_shopSheetList; }
	Basket * GetBasket() { return p_basket; }
	Receipt * GetReceipt() { return p_receipt; }

private:
	bool validateShoppingNote(string s, int * p_number, string * p_name, float * p_price);
	bool isValidProductNumber(const std::string &s);
	bool isValidPrice(const std::string &s);

	// Wrong input notes counter
	int discardedNotesCnt;

	// Link to the input
	InputProvider * p_input;

	// Provider Shopping list
	ShoppingSheetList * p_shopSheetList;

	// Container for product
	Basket * p_basket;

	// Receipt
	Receipt * p_receipt;

	// Max product number allowed as input
	static const int ProductNumberMax;

	// Minimum digit allowed for product name as input
	static const int ProducNameCharacterMin;
};

#endif /* APPLICATION_H_ */
