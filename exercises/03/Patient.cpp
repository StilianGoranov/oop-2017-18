#include "Patient.h"
#include "Nurse.h"

void Patient::setName(char const* _name)
{
	int len = strlen(_name) + 1;
	if (len < 50)
		strcpy_s(this->name, len, _name);
	else
		std::cout << "Too much length!";
}

void Patient::setIllness(char const* _illness)
{
	int len = strlen(_illness) + 1;
	if (len < 50)
		strcpy_s(this->illness, len, _illness);
	else
		std::cout << "Too much length!";
}

Patient::Patient(char const* _name, int _age, char const* _illness,
	int _floorInHospital, Nurse const* _nurse)
{
	setAge(_age);
	setName(_name);
	setNurse(_nurse);
	setFloorInHospital(_floorInHospital);
	setIllness(_illness);
}

void Patient::setNurse(Nurse const* _nurse)
{
	this->nurse = _nurse;
}

void Patient::setAge(int _age) 
{
	if (_age >= 0 && _age <= 120)
		this->age = _age;
	else
	{
		this->age = 0;
		std::cout << "Invalid age! Set to 0";
	}		
}

void Patient::setFloorInHospital(int _floorInHospital)
{
	if (_floorInHospital >= 0 && _floorInHospital <= 10)
		this->floorInHospital = _floorInHospital;
	else
	{
		this->floorInHospital = 0;
		std::cout << "Invalid floor! Set to 0";
	}
}

void Patient::print() const
{
	std::cout << "Patient name: " << this->name << '\n';
	std::cout << "Age: " << this->age << '\n';
	std::cout << "Illness: " << this->illness << '\n';
	std::cout << "Floor: " << this->floorInHospital << '\n';
	if (this->nurse != nullptr)
		std::cout << "Nurse taking care of him: " << this->nurse->getName() << '\n';
	else
		std::cout << "No nurse is taking care of him!\n";
}

void Patient::callNurse() const
{
	if (this->nurse != nullptr)
		std::cout << "Patient " << this->name << " needs help from nurse " << this->nurse->getName() << "!\n";
	else
		std::cout << "Patient " << this->name << " needs help, no nurse takes care of him!\n";
}
