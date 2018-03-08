#include "Patient.h"
#include "Nurse.h"
#include <iostream>

// default constructor
Patient::Patient()
{
	setAge(0);
	setName("Pe6o");
	setIllness("Cold");
	setFloor(5);
	setNurse(nullptr);
}

// constructor with parameters
Patient::Patient(char const* _name, int _age, char const* _illness,
	int _floor, Nurse* _nurse)
{
	setAge(_age);
	setName(_name);
	setIllness(_illness);
	setFloor(_floor);
	setNurse(nurse);
}

// setters
void Patient::setName(char const* _name)
{
	if (strlen(_name) >= 50)
		std::cout << "Too much length in name!\n";
	else
		strcpy_s(name, strlen(_name) + 1, _name);
}

void Patient::setAge(int _age)
{
	if (_age < 0 || _age > 120)
		std::cout << "Invalid age!" << std::endl;
	else
		age = _age;
}

void Patient::setIllness(char const* _illness)
{
	if (strlen(_illness) >= 50)
		std::cout << "Too much length in illness!\n";
	else
		strcpy_s(illness, strlen(_illness) + 1, _illness);
}

void Patient::setFloor(int _floor)
{
	if (_floor < 0 || _floor > 10)
		std::cout << "Invalid floor!\n";
	else
		floor = _floor;
}

void Patient::setNurse(Nurse* _nurse)
{
	nurse = _nurse;
}

// getters
char const* Patient::getName() const
{
	return name;
}

int Patient::getAge() const
{
	return age;
}

char const* Patient::getIllness() const
{
	return illness;
}

int Patient::getFloor() const
{
	return floor;
}

Nurse* Patient::getNurse() const
{
	return nurse;
}

// utility methods
void Patient::print() const
{
	std::cout << "Patient name: " << name << std::endl;
	std::cout << "Ilness: " << illness << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Floor: " << floor << std::endl;

	if (nurse == nullptr)
		std::cout << "Nobody takes care of him currently.\n";
	else
		std::cout << "Nurse " << nurse->getName() << std::endl;
}

void Patient::callNurse() const
{
	std::cout << "Patient " << name << " calls for help!\n";
}
