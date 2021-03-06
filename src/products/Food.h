/*******************************************************************************
	File        : Food.h
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Food class header
*******************************************************************************/

#ifndef FOOD_H_
#define FOOD_H_

// Include
#include "GenericProduct.h"

// Class that implements the Food product
class Food : public GenericProduct
{
public:
	Food(string name, int num, float price);
	~Food();
};

#endif /* FOOD_H_ */
