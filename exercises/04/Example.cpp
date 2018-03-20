#include<iostream>
/*
    A VERY limited realization of an integer vector to demonstrate the things we learned about in the last lab
*/


class Vector {
private:
    int size;
    int capacity;
    int *arr;
    void extend();
    void del();
    void copy(const Vector& other);
public:
    // Big 4
    Vector();
    Vector(int _capacity);
    Vector(const Vector& other);
    ~Vector();
    Vector& operator=(const Vector& other);

    void toEnd(int num);
    void print() const;
};

void Vector::extend()
{
    int* old = arr;
    capacity *=2; // Extend is an expensive operation. Doubling the capacity allows us to call it less often.
    arr = new int[capacity];

    for(int i = 0 ; i < size ; i++)
    {
        arr[i] = old[i];
    }

    delete [] old;
}

void Vector::del()
{
    delete [] arr;
}

void Vector::copy(const Vector& other)
{
    size = other.size;
    capacity = other.capacity;
    arr = new int[capacity];
    for (int i = 0 ; i < size ; i++)
    {
        arr[i] = other.arr[i];
    }
}

/// Constructor
Vector::Vector(): size(0), capacity(1)
{
    arr = new int[1];
}

/// Parameterized Constructor
Vector::Vector(int _capacity): size(0), capacity(_capacity)
{
    arr = new int[capacity];
}

/// Destructor
Vector::~Vector()
{
    del();
}

/// Copy Constructor
Vector::Vector(const Vector& other)
{
    copy(other);
}

/// Operator=
Vector& Vector::operator=(const Vector& other)
{
    if (this != &other) // We don't have to copy a vector if it is the same
    {
        del();
        copy(other);
    }

    return *this; // cascading
}

void Vector::toEnd(int number)
{
    if (size == capacity)
    {
        extend();
    }

    arr[size++] = number;
}

void Vector::print() const
{
    for (int i = 0; i < size ; i++)
    {
        std::cout<<arr[i]<<" ";
    }
}

int main()
{
    Vector a;
    a.toEnd(1);
    a.toEnd(2);
    a.toEnd(3);
    a.print();
    std::cout<<std::endl;
    Vector b = a;
    b.print();
    std::cout<<std::endl;
    Vector c;
    c = b;
    c.print();
    return 0;
}
