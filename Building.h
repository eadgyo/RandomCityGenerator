#ifndef __BUILDING__
#define __BUILDING__
#include <iostream>
#include "Constant.h"
#include "tools.h"
using namespace std;
struct Building
{
	Building():sName(""), remaining(0)
	{
	};
	string sName;
	int remaining;
};

#endif