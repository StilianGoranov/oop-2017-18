#include <iostream>
using namespace std;

class Animal
{
public:
	virtual void makeSound() = 0;
	virtual ~Animal()
	{
		cout << "Animal destroyed!\n";
	}
};

void Animal::makeSound()
{
	cout << "HAHAHA" << endl;
}

class Dog : public Animal
{
public:

	virtual void makeSound() override 
	{
		cout << "I am a dog" << endl;
	}

	virtual ~Dog()
	{
		cout << "Dog destroyed!\n";
	}

};

class Cat : public Animal
{
public:
	virtual void makeSound() override
	{
		cout << "I am a cat" << endl;
	}

	virtual ~Cat()
	{
		cout << "Animal destroyed!\n";
	}

};

class Dakel : public Dog
{
public:
	virtual void makeSound() override
	{
		cout << "I am a dakel" << endl;
	}

	virtual ~Dakel()
	{
		cout << "Dakel destroyed!\n";
	}

};

class Bird : public Animal
{
public:
	virtual void makeSound() override
	{
		cout << "I am a bird" << endl;
	}

	virtual ~Bird()
	{
		cout << "Animal destroyed!\n";
	}
};

void test_polymorphism()
{
	Dog d, d1, d2;
	Cat c;
	Bird b, b1;
	Dakel dakel;

	Animal* zoo[7];
	zoo[0] = &d;
	zoo[1] = &c;
	zoo[2] = &b;
	zoo[3] = &d2;
	zoo[6] = &b1;
	zoo[5] = &d2;
	zoo[4] = &dakel;

	for (Animal* a : zoo)
	{
		auto dPtr = dynamic_cast<Dog*>(a);
		if (dPtr != nullptr)
			dPtr->makeSound();
		else
			cout << "Not a dog!" << endl;
	}
}

void test_destructors()
{
	Animal* a = new Dakel();
	delete a;
}

int main()
{
	// test_polymorphism();
	test_destructors();

	return 0;
}
