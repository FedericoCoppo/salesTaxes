/*******************************************************************************
	File        : InputProvider.h
	Date        : 16/11/2020
	Author      : Federico Coppo
	Description : Input provider class header
*******************************************************************************/

#ifndef INPUTPROVIDER_H_
#define INPUTPROVIDER_H_

// Include
#include <map>
#include "ShoppingSheetList.h"

// Class to manage input
class InputProvider
{
public:

	// input source
	typedef enum
	{
		hardCoded,
		file,

	} InputSource;

	InputProvider();
	virtual ~InputProvider();
	ShoppingSheetList * InputCreate(InputSource inSource, const char * inputPath = NULL, const char * vocabPath = NULL);
	int GetUser() { return UserTestID; }
	int GetMapProductCategorySize() { return MapProductCategory.size(); }

private:
	void hardCodedInputCreate();
	void hardCodedWrongInputCreate();
	bool fileInputReader (const char * path);
	bool fileCatVocabularyReader (const char * path);
	bool getNoteCategory(string note, ShoppingNote::productCategory * cat);
	void clearShoppingSheet(ShoppingSheetList * p_list);
	static string convertStringToUpper(string s);

	InputSource source;
	bool isInputCreated;
	bool isCategoryVocabularyOpened;
	ShoppingSheetList * p_shopSheetList;
	map <string,string> MapProductCategory;

	// Configuration static parameter
	static const unsigned char UserTestID;
	static const bool WrongHardCodedInput;
};

#endif /* INPUTPROVIDER_H_ */
