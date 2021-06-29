#include "point.h"
#include <iostream>

extern "C"
{
	void nc::version()
	{
		std::cout << "version 2" << std::endl;
	}
}
