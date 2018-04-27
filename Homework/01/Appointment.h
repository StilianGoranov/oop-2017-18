#ifndef _APPOINTMENT_H
#define _APPOINTMENT_H

#include "Time.h"

class Appointment
{
private:
	Time t;
	char* person;

public:
	Appointment(Time _t = Time(), char const* _person = nullptr)
		: person(nullptr), t(_t)
	{
		setPerson(_person);
	}

	Appointment(Appointment const& other)
		: Appointment(other.t, other.person)
	{}

	Appointment& operator=(Appointment const& other)
	{
		if (this != &other)
		{
			setTime(other.t);
			setPerson(other.person);
		}

		return *this;
	}

	~Appointment()
	{
		delete[] person;
	}

	void setPerson(char const* _person)
	{
		if (_person == nullptr)
			_person = "";

		int len = strlen(_person) + 1;
		delete[] person;
		person = new char[len];
		strcpy_s(person, len, _person);
	}

	char const* getPerson() const { return person; }

	void setTime(Time const& _t) { t = _t; }
	Time getTime() const { return t; }

	void print(std::ostream& os = std::cout) const
	{
		os << t << " -> " << person;
	}
};

std::ostream& operator<<(std::ostream& os, Appointment const& a)
{
	a.print(os);
	return os;
}

bool operator<(Appointment const& a1, Appointment const& a2)
{
	return a1.getTime() < a2.getTime();
}

#endif 
