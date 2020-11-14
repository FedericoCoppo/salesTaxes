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

#include "Product.h"
#include "Basket.h"
#include "ReceiptGenerator.h"


using namespace std;

// Class that implement the Application
class Application
{
public:
	Application(void);
	virtual ~Application(void);
	void KeepProduct(Product * p_product, Basket * p_basket);

	void PrintLine(const char * pt);
	void PrintString(string s);

private:

};

#endif /* APPLICATION_H_ */
