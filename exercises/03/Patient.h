#ifndef _PATIENT_H
#define _PATIENT_H

class Nurse;

class Patient
{
private:
	char name[50];
	int age;
	char illness[50];
	int floor;
	Nurse* nurse;

public:
	// default constructor
	Patient();

	// constructor with parameters
	Patient(char const* _name, int _age, char const* illness,
		int _floor, Nurse* _nurse);

	// setters
	void setName(char const* _name);
	void setAge(int _age);
	void setIllness(char const* _name);
	void setFloor(int _floor);
	void setNurse(Nurse* _nurse);

	// getters
	char const* getName() const;
	int getAge() const;
	char const* getIllness() const;
	int getFloor() const;
	Nurse* getNurse() const;

	// utility methods
	void print() const;
	void callNurse() const;
};

#endif
