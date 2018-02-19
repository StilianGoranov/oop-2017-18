#include <iostream>
using Function = double(*)(double);
using NextFunction = int(*)(int);
using BinOperation = double(*)(double, double);

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

int multIter(int a, int b)
{
	int result = 1;
	for (int i = a; i <= b; i++)
	{
		result *= i;
	}

	return result;
}

int multRec(int a, int b)
{
	if (a > b)
		return 1;

	return a * multRec(a + 1, b);
}

// higher-order function
// takes functions as parameters
int accumulate(int a, int b, BinOperation op,
	Function f, NextFunction nextf, int base)
{
	if (a > b)
		return base;

	return op(f(a), accumulate(nextf(a), b, op, f, nextf, base));
}

double add(double x, double y) { return x + y; }
int addOne(int x) { return x + 1; }
double mult(double x, double y) { return x * y; }
double id(double x) { return x; }
double square(double x) { return x * x; }
int addTwo(int x) { return x + 2; }

// demonstrating the use of accumulate
int sumAcc(int a, int b)
{
	return accumulate(a, b, add, id, addOne, 0);
}

int multAcc(int a, int b)
{
	return accumulate(a, b, mult, id, addOne, 1);
}

int sumSquares(int a, int b)
{
	return accumulate(a, b, add, square, addOne, 0);
}

int sumSquaresSkip(int a, int b)
{
	return accumulate(a, b, add, square, addTwo, 0);
}

void testAccumulate()
{
	std::cout << sumAcc(1, 10) << std::endl;
	std::cout << sumSquares(1, 3) << std::endl;
	std::cout << sumSquaresSkip(1, 3) << std::endl;
	std::cout << multAcc(1, 5) << std::endl;
}

// derivative of a function
// demonstrating a higher-order function which returns another function
Function function = nullptr;
double const EPS = 0.0001;

double derivative(double x)
{
	return (function(x + EPS) - function(x)) / EPS;
}

Function derive(Function f)
{
	function = f;
	return derivative;
}

void testDerivative()
{
	std::cout << derive(square)(5) << std::endl; // f(x) = x^2 ; f'(x) = 2x ; f'(5) = 10
}

int main()
{
	testAccumulate();
	testDerivative();

	return 0;
}
