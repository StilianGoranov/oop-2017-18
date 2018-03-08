#include "Hospital.h"

void testHospital()
{
	// initializing nurses and patients using constructor with parameters
	Nurse n1("Galena", 3);
	Nurse n2("Nikoleta", 1);

	Patient p1("Georgi Ivanov Gonzo", 30, "Svruh doza narkotici", 3, &n1);
	Patient p2("Hristo Stoichkov", 50, "Mnogo psuvane", 5, &n2);

	
	Hospital h("Sofia MED", true);
	h.addNurse(n1);
	h.addNurse(n2);
	h.addPatient(p1);
	h.addPatient(p2);

	h.print();

	p1.callNurse();
	n1.help(p1);

	p2.callNurse();
	n2.help(p2);

	h.removeNurse(n2);
	h.removePatient(p1);

	h.print();
}

int main()
{
	testHospital();

	return 0;
}
