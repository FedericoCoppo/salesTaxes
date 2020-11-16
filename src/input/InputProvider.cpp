/*******************************************************************************
	File        : InputProvider.cpp
	Date        : 16/11/2020
	Author      : Federico Coppo
	Description : Input Provider class:
				  it provide input to application
*******************************************************************************/

#include "InputProvider.h"

// static attribute
const unsigned char InputProvider::User = 1;
const bool InputProvider::WrongInput = false;

// Constructor
InputProvider::InputProvider()
{
	p_shopSheetList = new ShoppingSheetList();
	isCreated = false;
}

// Destructor
InputProvider::~InputProvider(void)
{
	clearShoppingSheet(p_shopSheetList);

	if (p_shopSheetList)
	{
		delete p_shopSheetList;
		p_shopSheetList = NULL;
	}
}

// Free the memory (ShoppingNotes of list)
void InputProvider::clearShoppingSheet(ShoppingSheetList * p_list)
{
	int max = p_list->GetShoppingNoteListSize();
	for (int i = 0; i < max; i++)
	{
		ShoppingNote * p_note = p_list->GetShoppingNote(i);

		if (p_note)
		{
			delete p_note;
		}
	}

	p_list->ClearNoteFromShoppingList();
}

// Create input
ShoppingSheetList * InputProvider::InputCreate()
{
	// Avoid overwrite multiple input for this provider
	if (!isCreated)
	{
		isCreated = true;

		// Create input
		if (WrongInput)
		{
			// wrong input data creation
			hardCodedWrongInputCreate();
		}
		else
		{
			// correct input data creation
			hardCodedInputCreate();
		}
	}

	return p_shopSheetList;
}

// Hard coded input data creation
void InputProvider::hardCodedInputCreate()
{
	// switch test input
	if (User == 1)
	{
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2 book at 12.49", ShoppingNote::productCategory::book));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 music CD at 14.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 chocolate bar at 0.85", ShoppingNote::productCategory::food));
	}
	else if (User == 2)
	{
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported box of chocolates at 10.00", ShoppingNote::productCategory::food));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 47.50", ShoppingNote::productCategory::genericProduct));
	}
	else if (User == 3)
	{

		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 27.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 bottle of perfume at 18.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 packet of headache pills at 9.75", ShoppingNote::productCategory::medicine));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("3 box of imported chocolates at 11.25", ShoppingNote::productCategory::food));
	}
	else if (User == 4)
	{

		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported box of chocolates at 10.50", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 54.65", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2 book at 12.495", ShoppingNote::productCategory::medicine));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("15 box of imported chocolate at 1", ShoppingNote::productCategory::food));
	}
}

// Hard coded input wrong data creation
void InputProvider::hardCodedWrongInputCreate()
{
	// good input
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported book at 12.49", ShoppingNote::productCategory::book));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2 chocolate bar at 1.25", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 cake at 2", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 milk at 1.", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 coke at .2", ShoppingNote::productCategory::food));

	// bad input
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2x coffè at 1.25", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("x2 chocolate bar at 1.25", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 music CD at XX", ShoppingNote::productCategory::genericProduct));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 music CD at 3.33x", ShoppingNote::productCategory::genericProduct));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("-1 cake at 13", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 cake at 13,2", ShoppingNote::productCategory::food));
	p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2 book at 0", ShoppingNote::productCategory::book));
}
