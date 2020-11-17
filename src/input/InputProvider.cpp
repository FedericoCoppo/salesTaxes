/*******************************************************************************
	File        : InputProvider.cpp
	Date        : 16/11/2020
	Author      : Federico Coppo
	Description : Input Provider class:
				  it provide input to application
*******************************************************************************/

// include
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <regex>

#include "InputProvider.h"

using namespace std;

// static attribute
const unsigned char InputProvider::UserTestID = 1;
const bool InputProvider::WrongHardCodedInput = false;

// Constructor
InputProvider::InputProvider()
{
	// default source is hard coded
	source = InputSource::hardCoded;
	isInputCreated = false;
	isCategoryVocabularyOpened = false;
	p_shopSheetList = new ShoppingSheetList();
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

// Free the memory of ShoppingNotes list's nodes
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

// Get the category from note using vocabulary map
bool InputProvider::getNoteCategory(string note, ShoppingNote::productCategory * cat)
{
	bool success = false;
	bool found = false;

	// default vaule for unknow categories
	*cat = ShoppingNote::productCategory::genericProduct;

	// Avoid creating notes without the vocabulary
	if (isCategoryVocabularyOpened)
	{
		string chunk;
		string categoryStr;
		std::stringstream test(note);

		// for each chunk check if present in the vocabulary
		while(std::getline(test, chunk, ' '))
		{
		    if (MapProductCategory.find(chunk) != MapProductCategory.end())
		    {
		        // if found, get the string value
		        categoryStr = MapProductCategory[chunk];
		        found = true;
		        break;
		    }
		}

		if (found)
		{
			// convert string value into category enum
			if (categoryStr == "BOOK")
			{
				*cat = ShoppingNote::productCategory::book;
			}
			else if (categoryStr == "FOOD")
			{
				*cat = ShoppingNote::productCategory::food;
			}
			else if (categoryStr == "MEDICINE")
			{
				*cat = ShoppingNote::productCategory::medicine;
			}
			else
			{
				*cat = ShoppingNote::productCategory::genericProduct; 	// "GENERIC" or unknow
			}
		}

		success = true;
	}

	return success;
}

// File input reader
bool InputProvider::fileInputReader (const char * path)
{
	bool success = false;
	fstream notesFile;
	notesFile.open(path,ios::in);

	if (notesFile.is_open())
	{
		string note;

		while(getline(notesFile, note))
		{
			ShoppingNote::productCategory catTmp;

			// Get the category from vocabulary
			if (getNoteCategory(note, &catTmp))
			{
				// Create the new note and push into list
				p_shopSheetList->AddShoppingNoteToList(new ShoppingNote(note, catTmp));
			}
		}

		success = true;
		notesFile.close();
	}
	else
	{
		cout << "Unable to open the file: " << path << "\n";
	}

	return success;
}

// Read vocabulary file
bool InputProvider::fileCatVocabularyReader (const char * path)
{
	bool success = false;
	fstream vocabularyFile;
	vocabularyFile.open(path,ios::in);

	if (vocabularyFile.is_open())
	{
		string line;
		string prodName;
		string prodCategory;

		while(getline(vocabularyFile, line))
		{
			// replace \t with space to consider also file with wrong format
			line = std::regex_replace(line, std::regex("\\t"), " ");

			prodName = line.substr(0, line.find(" "));
			prodCategory = line.erase(0, prodName.length() + 1);

			// remove spurious space
			prodName = std::regex_replace(prodName, std::regex(" "), "");
			prodCategory = std::regex_replace(prodCategory, std::regex(" "), "");

			prodCategory = convertStringToUpper(prodCategory);

			// Remove spaces
		    prodName.erase(std::remove_if(prodName.begin(), prodName.end(), ::isspace), prodName.end());
		    prodCategory.erase(std::remove_if(prodCategory.begin(), prodCategory.end(), ::isspace), prodCategory.end());

			// Check the allowed category
			if ( prodCategory == "FOOD" || prodCategory == "BOOK" || prodCategory == "MEDICINE" || prodCategory == "GENERIC" )
			{
				// Push the new product name into map [KEY = product, VALUE = Category]
				MapProductCategory.insert(make_pair(prodName,prodCategory));
			}
		}

		if (MapProductCategory.size() >= 1)
		{
			success = true;
		}

		vocabularyFile.close();
	}
	else
	{
		cout << "Unable to open the file: " << path << "\n";
	}

	return success;
}

// Create the input
ShoppingSheetList * InputProvider::InputCreate(InputSource inSource, const char * inputPath, const char * vocabPath)
{
	// Avoid overwrite multiple input for this provider
	if (!isInputCreated)
	{
		if (inSource == InputSource::hardCoded)
		{
			isInputCreated = true;
			source = inSource;

			if (WrongHardCodedInput)
			{
				// Wrong hard coded input data creation (only for test purpose)
				hardCodedWrongInputCreate();
			}
			else
			{
				// Correct input data creation
				hardCodedInputCreate();
			}
		}
		else if (inSource == InputSource::file)
		{
			// Read the vocabulary
			if (vocabPath != NULL)
			{
				if (fileCatVocabularyReader(vocabPath))
				{
					isCategoryVocabularyOpened = true;

					if (inputPath != NULL)
					{
						if (fileInputReader(inputPath))
						{
							isInputCreated = true;
							source = inSource;
						}
					}
				}
			}
		}
	}

	return p_shopSheetList;
}

// Hard coded input data creation
void InputProvider::hardCodedInputCreate()
{
	// switch test input
	if (UserTestID == 1)
	{
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("2 book at 12.49", ShoppingNote::productCategory::book));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 music CD at 14.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 chocolate bar at 0.85", ShoppingNote::productCategory::food));
	}
	else if (UserTestID == 2)
	{
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported box of chocolates at 10.00", ShoppingNote::productCategory::food));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 47.50", ShoppingNote::productCategory::genericProduct));
	}
	else if (UserTestID == 3)
	{

		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 imported bottle of perfume at 27.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 bottle of perfume at 18.99", ShoppingNote::productCategory::genericProduct));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("1 packet of headache pills at 9.75", ShoppingNote::productCategory::medicine));
		p_shopSheetList->AddShoppingNoteToList(new ShoppingNote("3 box of imported chocolates at 11.25", ShoppingNote::productCategory::food));
	}
	else if (UserTestID == 4)
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

// Convert a string into corresponding upper case string
string InputProvider::convertStringToUpper(string s)
{
	// convert string to back to lower case
	std::for_each(s.begin(), s.end(), [](char & c){
		c = ::toupper(c);
	});

	return s;
}

