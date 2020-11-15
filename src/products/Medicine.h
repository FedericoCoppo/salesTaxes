/*******************************************************************************
	File        : Medicine.h
	Date        : 15/11/2020
	Author      : Federico Coppo
	Description : Medicine class header
*******************************************************************************/

#ifndef MEDICINE_H_
#define MEDICINE_H_

// include
#include "Product.h"

// Class that implements the Medicine product
class Medicine : public Product
{
public:
	Medicine(string name, int num, float price);
	~Medicine();
};

#endif /* MEDICINE_H_ */
