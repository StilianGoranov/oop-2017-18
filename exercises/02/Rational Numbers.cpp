#include<iostream>

using namespace std;

int euclid(int a, int b)
{
    while (a != 0 && b != 0)
    {
        if (b > a)
        {
            std::swap(a,b);
        }
        a -= b;
    }
    if (a > b ) std::swap(a,b);

    return a ? a : b;
}

struct Rational
{
    int nom, denom;

    void normalize()
    {
        int gcd = euclid(nom, denom);
        nom /= gcd;
        denom /= gcd;
    }

    double value()
    {
        return (double)nom / denom;
    }

    void add(Rational other)
    {
        nom = nom * other.denom + other.nom * denom;
        denom *= other.denom;
        normalize();
    }

    void subtract(Rational other)
    {
        nom = nom * other.denom - other.nom * denom;
        denom *= other.denom;
        normalize();
    }

    void multiply(Rational other)
    {
        nom *= other.nom;
        denom *= other.denom;
        normalize();
    }

    void divide(Rational other)
    {
        nom *= other.denom;
        denom *= other.nom;
        normalize();
    }

    void print()
    {
        if (denom == 1)
        {
            std::cout<<nom<<std::endl;
        }
        else
        {
            std::cout<<nom<<"/"<<denom<<std::endl;
        }
    }
};

int main()
{
    Rational a;
    a.nom = 2;
    a.denom = 4;
    a.print();
    a.normalize();
    a.print();
    std::cout<<a.value()<<std::endl;
    a.divide(a);
    a.print();
}
