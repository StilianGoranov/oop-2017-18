#include "Hospital.h"

void Hospital::setName(char const* _name)
{
	int len = strlen(_name) + 1;
	if (len < 50)
		strcpy_s(this->name, len, _name);
	else
		std::cout << "Too much length!";
}

void Hospital::setIsPrivateHospital(bool _isPrivateHospital)
{
	this->isPrivateHospital = _isPrivateHospital;
}

Hospital::Hospital(char const* _name, bool _isPrivateHospital)
	: numberOfNurses(0), numberOfPatients(0)
{
	setName(_name);
	setIsPrivateHospital(_isPrivateHospital);
}

void Hospital::addPatient(Patient const& newPatient)
{
	if (numberOfPatients == MAX_PATIENTS)
		std::cout << "Cannot accept more patients!\n";
	else
		patients[numberOfPatients++] = newPatient;
}

void Hospital::removePatient(Patient const& oldPatient)
{
	for (int i = 0; i < numberOfPatients; ++i)
		if (strcmp(patients[i].getName(), oldPatient.getName()) == 0 &&
			strcmp(patients[i].getIllness(), oldPatient.getIllness()) == 0)
		{
			patients[i] = patients[--numberOfPatients];
			std::cout << "Patient " << oldPatient.getName() << " is released!\n";
			break;
		}
}

void Hospital::addNurse(Nurse const& newNurse)
{
	if (numberOfNurses == MAX_NURSES)
		std::cout << "Cannot hire more nurses!\n";
	else
		nurses[numberOfNurses++] = newNurse;
}
void Hospital::removeNurse(Nurse const& oldNurse)
{
	for (int i = 0; i < numberOfNurses; ++i)
		if (strcmp(nurses[i].getName(), oldNurse.getName()) == 0 && nurses[i].getYearsOfWork() == oldNurse.getYearsOfWork())
		{
			nurses[i] = nurses[--numberOfNurses];
			std::cout << "Nurse " << oldNurse.getName() << " is fired!\n";
			break;
		}
}

void Hospital::print() const
{
	std::cout << "---------------\n";
	std::cout << "Hospital name: " << this->name << '\n';
	std::cout << "Private hospital: " << std::boolalpha << this->isPrivateHospital << "\n\n";

	std::cout << "Number of nurses: " << this->numberOfNurses << '\n';
	for (int i = 0; i < numberOfNurses; ++i)
	{
		nurses[i].print();
		std::cout << '\n';
	}
		
	std::cout << "Number of patients: " << this->numberOfPatients << '\n';
	for (int i = 0; i < numberOfPatients; ++i)
	{
		patients[i].print();
		std::cout << '\n';
	}
}
