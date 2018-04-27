#ifndef _COMPANY_H
#define _COMPANY_H

#include "Worker.h"

class Company
{
private:
	char* name;

	Worker* workers;
	int capacity;
	int size;

	void copyWorkers(Company const& company);
	void resize(int newCapacity);
	void erase();

public:
	// big 4
	Company(char const* _name = nullptr);
	Company(Company const& company);
	Company& operator=(Company const& company);
	~Company();

	// setters and getters
	void setName(char const* _name);

	char const* getName() const { return name; }
	int getSize() const { return size; }
	int getCapacity() const { return capacity; }

	// utility methods
	void addWorker(Worker const& newWorker);
	void removeByName(char const* name);

	void sort(); // sorting workers by salary
	void print() const;
};

Company::Company(char const* _name)
	: name(nullptr), size(0), capacity(1)
{
	workers = new Worker[1];
	setName(_name);
}

Company::Company(Company const& company)
{
	setName(company.name);
	copyWorkers(company);
}

Company& Company::operator=(Company const& company)
{
	if (this != &company)
	{
		erase();
		setName(company.name);
		copyWorkers(company);
	}

	return *this;
}

Company::~Company()
{
	erase();
}

void Company::addWorker(Worker const& newWorker)
{
	if (size == capacity)
		resize(capacity * 2);

	workers[size++] = newWorker;
}

void Company::removeByName(char const* name)
{
	for (int i = 0; i < size; ++i)
	{
		if (strcmp(name, workers[i].getName()) == 0)
		{
			workers[i] = workers[--size];
			std::cout << "Worker " << name << " removed from company.\n";
			break;
		}
	}

	if (capacity / 4 >= size)
	{
		resize(capacity / 2);
		std::cout << "Capacity reduced twice!\n";
	}

}

void Company::resize(int newCapacity)
{
	if (newCapacity == 0)
	{
		workers = new Worker[1];
		size = 0;
		capacity = 1;
	}

	else if (newCapacity >= size)
	{
		Worker* newWorkers = new Worker[newCapacity];

		for (int i = 0; i < size; ++i)
			newWorkers[i] = workers[i];

		delete[] workers;
		workers = newWorkers;

		capacity = newCapacity;
	}

	else
		std::cout << "Possible loss of data! Did not change capacity!" << std::endl;
}

void Company::erase()
{
	delete[] name;
	delete[] workers;
}

void Company::copyWorkers(Company const& company)
{
	workers = new Worker[company.capacity];
	capacity = company.capacity;
	size = company.size;

	for (int i = 0; i < company.size; ++i)
		workers[i] = company.workers[i];
}

void Company::setName(char const* _name)
{
	if (_name == nullptr)
		_name = "";

	int len = strlen(_name) + 1;
	delete[] this->name;
	this->name = new char[len];
	strcpy_s(this->name, len, _name);
}

void Company::print() const
{
	std::cout << "Company's name: " << name << std::endl;
	std::cout << "Workers: " << size << std::endl;
	std::cout << "Capacity for workers: " << capacity << std::endl << std::endl;
	for (int i = 0; i < size; ++i)
	{
		workers[i].print();
		std::cout << std::endl;
	}

	if (size == 0)
		std::cout << "No workers currently.\n";
}

void Company::sort()
{
	for (int i = 0; i < size - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (workers[j].getSalary() < workers[minIndex].getSalary())
				minIndex = j;
		}

		std::swap(workers[minIndex], workers[i]);
	}
}

#endif 
