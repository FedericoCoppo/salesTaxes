/*******************************************************************************
	File        : Book.h
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Book class header
*******************************************************************************/

#ifndef BOOK_H_
#define BOOK_H_

// include
#include "GenericProduct.h"

// Class that implements the Book product
class Book : public GenericProduct
{
public:
	Book(string name, int num, float price);
	~Book();
};

#endif /* BOOK_H_ */
