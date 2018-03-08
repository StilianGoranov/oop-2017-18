#include "Nurse.h"

#include <iostream>

Nurse::Nurse()
{
	setName("Gergana");
}

void Nurse::setName(char const* _name)
{
	if (strlen(_name) >= 50)
		std::cout << "Too much length in name!\n";
	else
		strcpy_s(name, strlen(_name) + 1, _name);
}
