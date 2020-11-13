/*******************************************************************************
	File        : main.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Main routine
*******************************************************************************/

// include

#include "main.h"

using namespace std;

int main()
{
#ifdef TEST_APPLICATION

	// testing application
	ApplicationTest * testApp_pt = new ApplicationTest();
	testApp_pt->Test();
	delete testApp_pt;

#else
	// release application


#endif


	return 0;
}

