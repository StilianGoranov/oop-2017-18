#ifndef _HOSPITAL_H
#define _HOSPITAL_H

#include "Nurse.h"
#include "Patient.h"

int const MAX_PATIENTS = 300;
int const MAX_NURSES = 100;

class Hospital
{
private:
	char name[50];
	bool isPrivateHospital;

	Nurse nurses[MAX_NURSES];
	int numberOfNurses;

	Patient patients[MAX_PATIENTS];
	int numberOfPatients;

public:
	// constructors
	Hospital(char const* _name = "", bool _isPrivateHospital = false);

	// setters
	void setName(char const* _name);
	void setIsPrivateHospital(bool _isPrivateHospital);

	// getters
	char const* getName() const { return name; }
	bool getIsPrivateHospital() const { return isPrivateHospital; }
	int getNumberOfNurses() const { return numberOfNurses; }
	int getNumberOfPatients() const { return numberOfPatients; };

	// utility methods
	void addPatient(Patient const& newPatient);
	void removePatient(Patient const& oldPatient);

	void addNurse(Nurse const& newNurse);
	void removeNurse(Nurse const& oldNurse);

	void print() const;
};

#endif 
