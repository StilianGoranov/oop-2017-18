#include "Nurse.h"
#include "Patient.h"
#include <iostream>

void Nurse::setName(char const* _name)
{
	int len = strlen(_name) + 1;
	if (len < 50)
		strcpy_s(this->name, len, _name);
	else
		std::cout << "Too much length!";
}

void Nurse::setYearsOfWork(int _yearsOfWork)
{
	if (_yearsOfWork >= 0 && _yearsOfWork <= 100)
		this->yearsOfWork = _yearsOfWork;
	else
		std::cout << "Invalid years of work!";
}

Nurse::Nurse(char const* _name, int _yearsOfWork)
{
	setName(_name);
	setYearsOfWork(_yearsOfWork);
}

void Nurse::print() const
{
	std::cout << "Nurse's name: " << this->name << '\n';
	std::cout << "Years of work in hospital: " << this->yearsOfWork << '\n';
}

void Nurse::help(Patient const& patient) const
{
	std::cout << "Nurse " << this->name << " helped patient " << patient.getName() << " sucessfully!\n";
}
