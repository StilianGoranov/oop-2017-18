#ifndef _WORKER_H
#define _WORKER_H

#include <iostream>

class Worker
{
private:
	char* name;
	char* position;
	double salary;

public:
	// constructor (default and with parameters simultaneously)
	Worker(char const* _name = nullptr, char const* _position = nullptr, double _salary = 0);

	// copy constuctor
	Worker(Worker const& worker);

	// predefining operator=
	Worker& operator=(Worker const& worker);

	// destructor
	~Worker();

	// setters
	void setName(char const* _name);
	void setPosition(char const* _position);
	void setSalary(double _salary);

	// getters
	char const* getName() const { return name; }
	char const* getPosition() const { return position; }
	double getSalary() const { return salary; }

	void print() const;
};

Worker::Worker(char const* _name, char const* _position, double _salary)
	: name(nullptr), position(nullptr)
{
	setName(_name);
	setPosition(_position);
	setSalary(_salary);
}

Worker::Worker(Worker const& worker) : Worker(worker.name, worker.position, worker.salary) {}

Worker& Worker::operator=(Worker const& worker)
{
	if (this != &worker)
	{
		setName(worker.name);
		setPosition(worker.position);
		setSalary(worker.salary);
	}

	return *this;
}

Worker::~Worker()
{
	delete[] name;
	delete[] position;
}

void Worker::setSalary(double _salary)
{
	if (_salary >= 0)
		this->salary = _salary;
	else
		this->salary = 0;
}

void Worker::setName(char const* _name)
{
	if (_name == nullptr)
		_name = "";

	int len = strlen(_name) + 1;
	delete[] this->name;
	this->name = new char[len];
	strcpy_s(this->name, len, _name);
}

void Worker::setPosition(char const* _position)
{
	if (_position == nullptr)
		_position = "";

	int len = strlen(_position) + 1;
	delete[] this->position;
	this->position = new char[len];
	strcpy_s(this->position, len, _position);
}

void Worker::print() const
{
	std::cout << "Worker name: " << name << std::endl;
	std::cout << "Worker position: " << position << std::endl;
	std::cout << "Worker salary: " << salary << std::endl;
}

#endif 
