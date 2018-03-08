#ifndef _PATIENT_H
#define _PATIENT_H

#include <iostream>

class Nurse;

class Patient
{
private:
	char name[50];
	int age;
	char illness[50];
	int floorInHospital;
	Nurse const* nurse;

public:
	// constructors
	// default constructor and constructor with parameters simultaneously
	Patient(char const* _name = "", int _age = 0, char const* _illness = "",
		int _floorInHospital = 0, Nurse const* _nurse = nullptr);

	// setters
	void setName(char const* _name);
	void setAge(int _age);
	void setIllness(char const* _illness);
	void setFloorInHospital(int _floorInHospital);
	void setNurse(Nurse const* _nurse);

	// getters
	char const* getName() const { return name; }
	int getAge() const { return age; }
	char const* getIllness() const { return illness; };
	int getFloorInHospital() const { return floorInHospital; };
	Nurse const* getNurse() const { return nurse; }

	// utility methods
	void callNurse() const;

	void print() const;
};

#endif 
