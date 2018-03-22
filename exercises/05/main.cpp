#include "Company.h"

void nl() { std::cout << std::endl; }

void testCompany()
{
	Worker w1("Gosho", "Cleaner", 50);
	Worker w2("Peter", "CEO", 15000);
	Worker w3("Anthony", "Painter", 600);
	Worker w4("Natalia", "Designer", 3000);
	Worker w5("Kalina", "Computer programmer", 5000);

	Company c("The players EOOD");

	c.print();
	nl();

	c.addWorker(w1);
	c.print();
	nl();

	c.addWorker(w2);
	c.print();
	nl();

	c.addWorker(w3);
	c.print();
	nl();

	c.addWorker(w4);
	c.print();
	nl();

	c.addWorker(w5);
	c.print();
	nl();

	c.sort(); // sort by salary
	std::cout << "Sorted by salary: \n";
	c.print();
	nl();

	// test copy constructor
	Company copyCtorTest(c);
	std::cout << "Copy ctor test---------------\n";
	copyCtorTest.print();
	nl();

	copyCtorTest.removeByName("Kalina");
	copyCtorTest.removeByName("Anthony");
	copyCtorTest.removeByName("Peter");
	copyCtorTest.print();
	nl();

	c.print(); // should have same data

	std::cout << "Copy ctor test finished-------------\n";

	c.removeByName("Natalia");
	c.removeByName("Peter");
	nl();

	c.print(); // still same capacity - 8

	c.removeByName("Gosho"); // reduces capacity to 4 (2 workers with 8 capacity => 2 workers with 4 capacity)
	nl();

	c.print();
	nl();

	c.removeByName("Anthony");
	c.removeByName("Kalina");
	c.print();
	nl();

	c.addWorker(w1);
	c.print();

}

int main()
{
	testCompany();

	return 0;
}
