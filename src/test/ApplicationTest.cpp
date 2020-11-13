/*******************************************************************************
	File        : ApplicationTest.cpp
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#include <assert.h>
#include "applicationTest.h"

// Const
ApplicationTest::ApplicationTest(void)
{
	app_pt = new Application();
}

// Dest
ApplicationTest::~ApplicationTest(void)
{
	if (app_pt != NULL)
	{
		delete app_pt;
		app_pt = NULL;
	}
}

// Main test routine for application class
void ApplicationTest::Test(void)
{

}

