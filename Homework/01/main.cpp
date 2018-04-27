#include "stdafx.h"
#include <iostream>
#include "Time.h"
#include "Appointment.h"
#include "Schedule.h"
#include <cassert>

void nl()
{
	std::cout << std::endl;
}

void testTime()
{
	Time t1, t2(10, 76), t3(26, 65);
	std::cout << t1; nl();
	std::cout << t2; nl();
	std::cout << t3; nl();

	Time t4(22, 40);
	std::cout << t4; nl();
	t4 += 80;
	assert(t1 == t4);
	std::cout << t4; nl();


	Time t5 = Time(10, 76) + Time(22, 40);
	assert(t5 == Time(9, 56));
	std::cout << t5; nl();

	int diff = Time(9, 30) - Time(10, 40);
	assert(diff == 70);

	assert(Time(10, 40) < Time(10, 50));
	assert(Time(10, 40) < Time(11, 0));
	assert(!(Time(10, 40) < Time(10, 30)));
	assert(!(Time(10, 40) < Time(9, 59)));

	Time r1, r2, r3;
	std::cin >> r1 >> r2 >> r3;
	std::cout << r1;
	std::cout << r2;
	std::cout << r3;
}

void testAppointment()
{
	Appointment a1(Time(10, 50), "Gosho Petrov");
	std::cout << a1 << std::endl;

	Appointment a2(a1);
	a2.setPerson("Petro Goshov");
	std::cout << a2 << std::endl;
}

void testSchedule1()
{
	Schedule s;
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(10, 30), "Petur Petrov"));
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(11,10), "Misha Vaglov"));
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(12,30), "Lanko Perimanko"));
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(14, 20), "Kosio Hadjiiski"));
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(14, 20), "Kosio Hadjiiski"));
	std::cout << s << std::endl;
	s.addAppointment(Appointment(Time(15, 10), "Dimitur Rangelov"));
	std::cout << s << std::endl;

	s.clearBetween(Time(11, 5), Time(14,30));
	std::cout << "Clear between 11:05 and 14:21" << std::endl << s << std::endl;

	std::cout << "Appointment number 0 changed to Ivan Ivanov:\n";
	s[0].setPerson("Ivan Ivanov");
	std::cout << s << std::endl;
}

void testSchedule2()
{
	Schedule s;
	s.addAppointment(Appointment(Time(22, 15), "p1"));
	s.addAppointment(Appointment(Time(19, 20), "p2"));
	s.addAppointment(Appointment(Time(18,55), "p3"));
	s.addAppointment(Appointment(Time(20), "p4"));
	s.addAppointment(Appointment(Time(19,30), "p5"));
	s.addAppointment(Appointment(Time(22, 20), "p6"));
	
	std::cout << s << std::endl;
	std::cout << "Clear:\n";
	s.clear();
	std::cout << s << std::endl;
}

void testSchedule3()
{
	Schedule s;
	s.addAppointment(Appointment(Time(22, 15), "p1"));
	s.addAppointment(Appointment(Time(19, 20), "p2"));
	s.addAppointment(Appointment(Time(18, 55), "p3"));
	s.addAppointment(Appointment(Time(20), "p4"));
	s.addAppointment(Appointment(Time(19, 30), "p5"));
	s.addAppointment(Appointment(Time(22, 20), "p6"));

	std::cout << s << std::endl;
	std::cout << "Sorting!\n";

	s.sort();

	for (int i = 0; i < s.getSize() - 1; ++i)
		assert(s[i] < s[i + 1]);

	std::cout << s << std::endl;
}

void testSort()
{
	int arr[]{ 4,5,1,2,8,6,7,9,3 };

	for (int i : arr)
		std::cout << i << ' ';
	nl();

	Sort::quickSort(arr, 0, 8);

	for (int i : arr)
		std::cout << i << ' ';
	nl();

	for (int i = 0; i < 8; ++i)
		assert(arr[i] < arr[i + 1]);
}

int main() {

	// testTime();
	// testAppointment();
	// testSort();
	// testSchedule1();
	// testSchedule2();
	testSchedule3();

	return 0;
}
