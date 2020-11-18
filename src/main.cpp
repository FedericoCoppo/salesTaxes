/*******************************************************************************
	File        : main.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Main routine
 *******************************************************************************/

// Include
#include "main.h"

int main()
{
#ifdef TEST_APPLICATION

	// Testing application
	ApplicationTest * testApp_pt = new ApplicationTest();
	testApp_pt->Test();
	delete testApp_pt;

#else
	// Release application


#endif

	cout << "\nProgram terminated..";
	return 0;
}

