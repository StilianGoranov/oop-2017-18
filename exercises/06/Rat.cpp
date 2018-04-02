// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>


class Rat
{
private:
int d;
int n;

public:
Rat(int _n, int _d)
: n(_n)
{
assert(_d != 0);
d = _d;
}

// friend function
friend Rat operator+(Rat const& lhs, Rat const& rhs)
{
return Rat(lhs.n * rhs.d + rhs.n * lhs.d, lhs.d * rhs.d);
} // R + R

friend Rat operator+(int lhs, const Rat& rhs)
{
return Rat(lhs, 1) + rhs;
} // int + R

friend Rat operator+(Rat const& lhs, int x)
{
return x + lhs;
} // R + int

// member function
Rat& operator+=(int x) // R += int
{
/* *this = *this + x;
return *this; */
return *this = *this + x;
}

Rat& operator+=(Rat const& r)
{

}

friend bool operator<(Rat const& r1, Rat const& r2) // R < R ?
{
return r1.n * r2.d < r1.d * r2.n; // int < int ?
}



friend bool operator>(Rat const& r1, Rat const& r2)
{
return r2 < r1;
}

friend bool operator>=(Rat const& r1, Rat const& r2)
{

}

friend std::ostream& operator<<(std::ostream& out, const Rat& r)
{
return out << "n = " << r.n << '\n' << "d = " << r.d << std::endl;
}

// cin >> R;
friend std::istream& operator>>(std::istream& is, Rat& r)
{
std::cout << "Enter n: ";
is >> r.n;

std::cout << "Enter d: ";
is >> r.d;

return is;
}

void print() const
{
std::cout << "n = " << n << '\n' << "d = " << d << std::endl;
}

// prefix ++
Rat& operator++()
{
return *this += 1;
}

// postfix ++
Rat operator++(int)
{
Rat oldValue = *this;
++*this;

return oldValue;
}

int& operator[](int index)
{
assert(index == 1 || index == 0);
return index == 0 ? n : d;
}

int const& operator[](int index) const
{
assert(index == 1 || index == 0);
return index == 0 ? n : d;
}

operator bool()
{
return n;
// return n != 0;
// return !(n==0);
}

operator double()
{
return (double) n / d;
}

};

int main()
{
Rat r1(1, 2);
const Rat r2(2, 3);

r1[0] = 5; 
std::cout << r1[0] << std::endl; // r1.n
std::cout << r2[1] << std::endl; // r2.d

std::cout << (bool)5 << std::endl;
std::cout << (bool)0 << std::endl;

std::cout << (bool) (r1) << std::endl;

std::cout << ((double)r1) << std::endl;

    return 0;
}
