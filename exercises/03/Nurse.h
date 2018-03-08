#ifndef _NURSE_H
#define _NURSE_H

class Nurse
{
private:
	char name[50];

public:

	Nurse();

	void setName(char const* _name);

	char const* getName() const { return name; }
};

#endif 
