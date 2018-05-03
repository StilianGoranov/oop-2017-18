## Multiple Inheritance, Virtual Base Classes

### Deadly Diamond of Doom (and alliteration)

```c++
#include<iostream>

class Animal
{
private:
    int age;
public:
    Animal(int _age): age(_age)
    {
        std::cout<<"Animal\n";
    }
    void doSomething() const
    {
        std::cout<<"Hello, I guess?\n";
    }
};

class Dog: public Animal
{
public:
    Dog(int _age): Animal(_age)
    {
        std::cout<<"Dog\n";
    }
};

class Cat: public Animal
{
public:
    Cat(int _age): Animal(_age)
    {
        std::cout<<"Cat\n";
    }
};

class CatDog: public Cat, public Dog
{
public:
    CatDog(int _age): Cat(_age), Dog(_age)
    {
        std::cout<<"CatDog\n";
    }
};

int main()
{
    std::cout<<sizeof(CatDog)<<std::endl;
    // 8 -> because it has 2 copies of age
    CatDog a(10);
    /*
    Animal //-> First calls the Cat constructor that calls the Animal constructor
    Cat
    Animal //-> Then calls the Dog constructor that calls the Dog constructor (the order for Cat and Dog depends on the order in the initializing list)
    Dog
    CatDog //-> Finally calls the CatDog constructor
    */

    // a.doSomething(); // ERROR: The CatDog class has 2 copies of the doSomething function and doesn't know which one to call
    // a.Animal::doSomething(); // This doesn't help. Both copies of doSomething belong to the class Animal
    a.Cat::doSomething(); // This works! We will now call the copy of doSomething that was inherited from the Cat class
}

```

A CatDog object looks like this: CatDog(Cat(Animal), Dog(Animal))
It contains all the data from Cat, Dog and Animal (twice)



### Virtual Inheritance

```c++
#include<iostream>

class Animal
{
private:
    int age;
public:
    Animal(int _age): age(_age)
    {
        std::cout<<"Animal\n";
    }
    void doSomething() const
    {
        std::cout<<"Hello, I guess?\n";
    }
};

class Dog: virtual public Animal // NEW KEYWORD
{
public:
    // The call to the Animal constructor will be ignored when we construct a CatDog object
    Dog(int _age): Animal(_age)
    {
        std::cout<<"Dog\n";
    }
};

class Cat: virtual public Animal // NEW KEYWORD
{
public:
    // The call to the Animal constructor will be ignored when we construct a CatDog object
    Cat(int _age): Animal(_age)
    {
        std::cout<<"Cat\n";
    }
};

class CatDog: public Cat, public Dog
{
public:
    // Animal is now considered a direct parent of CatDog, CatDog must be the one to call the Animal constructor
    CatDog(int _age): Cat(_age), Dog(_age), Animal(_age)
    {
        std::cout<<"CatDog\n";
    }
};

int main()
{
    std::cout<<sizeof(Animal)<<std::endl; // 4 bytes for age
    std::cout<<sizeof(Cat)<<std::endl; // 4 bytes for age + sizeof(ptr)
    std::cout<<sizeof(CatDog)<<std::endl; // 4 bytes for age + 2*sizeof(ptr)
    CatDog a(10);
    /*
    Animal //-> CatDog calls every constructor. Animal is first even though it was last in the list.
    Cat
    Dog
    CatDog //-> Finally calls the CatDog constructor
    */
    // Notice how Animal is only called once. (There is only one copy of it in CatDog now)

    a.doSomething();
    a.Animal::doSomething();
    a.Cat::doSomething();
    // All of the above work because there is only one copy of doSomething now
}

```

A CatDog object now looks like this: CatDog(Cat(ptrToAnimal), Dog(ptrToAnimal), Animal)
It contains: All the data from Cat including an added pointer to Animal, all the data from Dog (again, including a pointer to Animal) and all the data from Animal. It no longer contains 2 copies of Animal.
