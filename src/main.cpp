/*******************************************************************************
	File        : main.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Main routine
 *******************************************************************************/

#include "main.h"

int main()
{
#ifdef TEST_APPLICATION

	// Testing application
	ApplicationTest * testApp_pt = new ApplicationTest();
	testApp_pt->Test();
	delete testApp_pt;

#else
	// release application


#endif

	cout << "\nprogram terminated..";
	return 0;
}

