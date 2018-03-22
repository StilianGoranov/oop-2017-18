#include <iostream>

class Person
{
private:
	char* name;

public:
	// big 4
	// default and with parameters constructor
	Person(char const* _name = nullptr);

	// operator=
	Person& operator=(Person const& other);

	// copy constructor
	Person(Person const& other);

	// destructor
	~Person();

	// setter
	void setName(char const* _name);

	char const* getName() const { return name; } // this->name }

	void print() const { std::cout << name << std::endl; }
};

Person::Person(char const* _name)
	: name{ nullptr }
{
	setName(_name);
}

Person::Person(Person const& other)
	: Person(other.name)
{}

Person& Person::operator=(Person const& other)
{
	if (this != &other)
		setName(other.name);

	return *this;
}

Person::~Person()
{
	delete[] name; // delete[] this->name;
}

void Person::setName(char const* _name)
{
	if (_name == nullptr)
		_name = "";

	int len = strlen(_name) + 1;

	delete[] name;
	name = new char[len];
	strcpy_s(name, len, _name);
}


int main()
{
	Person p1("Gosho");
	Person p2("Pe6o");

	p1.print();
	p2.print();

	Person p3(p1);
	p3.print();

	p3.setName("Aleks");
	p1.print();
	p3.print();

	Person p4;
	p4 = p1;
	p4.print();

    return 0;
}
