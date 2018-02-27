#include <iostream>
using Function = int(*)(int);
using NextFunction = int(*)(int);
using BinOperation = int(*)(int, int);

int sumIter(int a, int b)
{
    int result = 0;
    for (int i = a; i <= b; i++)
    {
        result += i;
    }

    return result;
}

int sumRec(int a, int b)
{
    if (a > b)
        return 0;

    return a + sumRec(a + 1, b);
}

int multRec(int a, int b)
{
    if (a > b)
        return 1;

    return a * multRec(a + 1, b);
}

int accumulate(int a, int b, BinOperation op, Function f, NextFunction nextf, int base)
{
    if (a > b)
        return base;

    return op(f(a), accumulate(nextf(a), b, op, f, nextf, base));
}

int add(int x, int y)
{
    return x + y;
}
int addOne(int x)
{
    return x + 1;
}
int mult(int x, int y)
{
    return x * y;
}
int id(int x)
{
    return x;
}

int sumAcc(int a, int b)
{
    return accumulate(a, b, add, id, addOne, 0);
}

int multAcc(int a, int b)
{
    return accumulate(a, b, mult, id, addOne, 1);
}

int square(int x)
{
    return x * x;
}

int sumSquares(int a, int b)
{
    return accumulate(a, b, add, square, addOne, 0);
}

int addTwo(int x)
{
    return x + 2;
}

int sumSquares1(int a, int b)
{
    return accumulate(a, b, add, square, addTwo, 0);
}

void testAccumulate()
{
    std::cout << sumAcc(1, 10) << std::endl;
    std::cout << sumSquares(1, 3) << std::endl;
    std::cout << sumSquares1(1, 3) << std::endl;
    std::cout << multAcc(1, 5) << std::endl;
}

int main()
{
    testAccumulate();

    return 0;
}
