#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "Appointment.h"
#include "Sort.h"
#include <cassert>

class Schedule
{
private:
	Appointment * aps;
	int size;
	int capacity;

	void resize(int newCapacity)
	{
		capacity = newCapacity;

		Appointment* temp = aps;
		aps = new Appointment[newCapacity];
		for (int i = 0; i < size; ++i)
			aps[i] = temp[i];

		delete[] temp;
	}

	void removeAppointment(int index)
	{
		aps[index] = aps[--size];
	}

	void copy(Schedule const& other)
	{
		capacity = other.capacity;
		size = other.size;
		aps = new Appointment[other.capacity];
		for (int i = 0; i < other.size; ++i)
			aps[i] = other.aps[i];
	}

	void erase()
	{
		delete[] aps;
	}

	void reduceCapacityIfNeeded()
	{
		if (size == 0)
			resize(1);
		else
		{
			int n = capacity / size;
			if (n >= 4)
				resize(capacity / (n / 2));
		}
	}

public:
	Schedule(int _capacity = 1)
		: size(0)
	{
		assert(_capacity > 0);
		capacity = _capacity;
		aps = new Appointment[_capacity];
	}

	Schedule(Schedule const& other)
	{
		copy(other);
	}

	Schedule& operator=(Schedule const& other)
	{
		if (this != &other)
		{
			erase();
			copy(other);
		}

		return *this;
	}

	~Schedule()
	{
		erase();
	}

	void addAppointment(Appointment const& newAppointment)
	{
		if (size == capacity)
			resize(capacity * 2);

		aps[size++] = newAppointment;
	}

	void clearBetween(Time const& t1, Time const& t2)
	{
		for (int i = 0; i < size; ++i)
			while (i < size && aps[i].getTime() >= t1 && aps[i].getTime() <= t2)
				removeAppointment(i);

		reduceCapacityIfNeeded();
	}

	void print(std::ostream& os = std::cout) const
	{
		os << "------------------------ Schedule -------------------\n";
		os << "Number of appointments: " << size << std::endl;
		os << "Capacity of schedule: " << capacity << std::endl;

		for (int i = 0; i < size; ++i)
			os << aps[i] << std::endl;
	}

	void clear()
	{
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = i + 1; j < size; ++j)
				while (j < size && aps[i].getTime() - aps[j].getTime() < 30)
					removeAppointment(j);

			reduceCapacityIfNeeded();
		}
		
	}

	int getSize() const { return size; }

	void sort()
	{
		Sort::quickSort(aps, 0, size - 1);
	}

	Appointment& operator[](int index)
	{
		assert(index >= 0 && index < size);
		return aps[index];
	}

	Appointment const& operator[](int index) const
	{
		assert(index >= 0 && index < size);
		return aps[index];
	}
};

std::ostream& operator<<(std::ostream& os, Schedule const& s)
{
	s.print(os);
	return os;
}

#endif 
