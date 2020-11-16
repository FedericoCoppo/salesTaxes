/*******************************************************************************
	File        : InputProvider.h
	Date        : 16/11/2020
	Author      : Federico Coppo
	Description : Input provider class header
*******************************************************************************/

#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_

// include
#include "ShoppingSheetList.h"

using namespace std;

// Class to manage input
class InputProvider
{
public:
	InputProvider();
	virtual ~InputProvider();
	ShoppingSheetList * InputCreate();
	int GetUser() { return User; }

private:
	void hardCodedInputCreate();
	void hardCodedWrongInputCreate();
	void clearShoppingSheet(ShoppingSheetList * p_list);

	ShoppingSheetList * p_shopSheetList;
	bool isCreated;

	// configuration parameter
	static const unsigned char User;
	static const bool WrongInput;
};
#endif /* INPUTPROVIDER_H_ */
