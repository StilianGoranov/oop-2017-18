#ifndef _NURSE_H
#define _NURSE_H

class Patient;

class Nurse
{
private:
	char name[50];
	int yearsOfWork;

public:
	// constructors
	// simultaneously default constructor and with parameters
	Nurse(char const* _name = "", int yearsOfWork = 0);

	// setters
	void setName(char const* _name);
	void setYearsOfWork(int _yearsOfWork);

	// getters
	char const* getName() const { return name; }
	int getYearsOfWork() const { return yearsOfWork; }

	// utility methods
	void help(Patient const& patient) const;

	void print() const;
};

#endif 
