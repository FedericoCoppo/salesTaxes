/*******************************************************************************
	File        : TestApplication.h
	Date        : 13/11/2020
	Author      : Federico Coppo
	Description : Test Application header
*******************************************************************************/

#ifndef TEST_APPLICATIONTEST_H_
#define TEST_APPLICATIONTEST_H_

#include "Application.h"

// Test application class
class ApplicationTest
{
public:
	ApplicationTest(void);
	virtual ~ApplicationTest(void);
	void Test(void);

private:

	Application * app_pt;

};

#endif /* TEST_APPLICATIONTEST_H_ */
