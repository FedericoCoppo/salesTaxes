/*******************************************************************************
	File        : Application.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Application header
 *******************************************************************************/

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <string>
#include "Product.h"
#include "Basket.h"

using namespace std;

// Class that implement the main application
class Application
{
public:

	Application(void);
	virtual ~Application(void);
	void ChooseProduct(Product * p_product, Basket * p_basket);
	void PrintLine(const char * pt);
	void PrintString(string s);

private:

};

#endif /* APPLICATION_H_ */
