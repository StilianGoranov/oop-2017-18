#include <iostream>
#include <iomanip>
using namespace std;

int const MAX_NAME = 50;
int const MAX_PRISONERS = 400;
char const* const IS_MURDERER = "TRUE";
char const* const NOT_MURDERER = "FALSE";

struct Prisoner
{
	char name[MAX_NAME];
	int prisonID;
	bool isMurderer;
	int numberOfCrimes;
};

void readPrisonerData(Prisoner& p)
{
	cout << "Enter prisoner's name: ";
	cin.getline(p.name, MAX_NAME);

	cout << "Enter prisoner's number: ";
	cin >> p.prisonID;

	char isMurderer[50];
	cin.getline(isMurderer, 6);
	do
	{
		cout << "Is the prisoner a murderer (enter TRUE or FALSE): ";
		cin.getline(isMurderer, 6);
	} while (strcmp(isMurderer, IS_MURDERER) != 0 && strcmp(isMurderer, NOT_MURDERER) != 0);

	if (strcmp(isMurderer, IS_MURDERER) == 0)
		p.isMurderer = true;
	else
		p.isMurderer = false;

	do
	{
		cout << "Enter number of crimes: ";
		cin >> p.numberOfCrimes;
	} while (p.numberOfCrimes <= 0);

	cin.get(); // skip '\n'
}

void tabulatePrisonerData(Prisoner const& prisoner)
{
	cout << setw(50) << left << prisoner.name
		<< setw(15) << prisoner.prisonID
		<< setw(15) << (prisoner.isMurderer ? IS_MURDERER : NOT_MURDERER)
		<< setw(15) << prisoner.numberOfCrimes << endl;
}

struct Prison
{
	char directorName[MAX_NAME];
	char prisonName[MAX_NAME];
	int numberOfPrisoners;
	Prisoner prisoners[MAX_PRISONERS];
};

void readPrisonData(Prison& prison)
{
	cout << "Enter prison's name: ";
	cin.getline(prison.prisonName, MAX_NAME);

	cout << "Enter directors's name: ";
	cin.getline(prison.directorName, MAX_NAME);

	do
	{
		cout << "Enter number of prisoners: ";
		cin >> prison.numberOfPrisoners;
	} while (prison.numberOfPrisoners < 0 && prison.numberOfPrisoners > MAX_PRISONERS);

	cin.get(); // skip '\n'

	for (int i = 0; i < prison.numberOfPrisoners; ++i)
	{
		readPrisonerData(prison.prisoners[i]);
		cout << endl;
	}
}

void tabulatePrisonData(Prison const& prison)
{
	cout << "--------------------\n";
	cout << left;
	cout << setw(50) << "Director's name"
		<< setw(30) << "Prison's name"
		<< "Number of prisoners\n"
		<< setw(50) << prison.prisonName
		<< setw(30) << prison.directorName
		<< prison.numberOfPrisoners << "\n";

	cout << "\nPrisoners data:\n\n";
	cout << setw(50) << "Name"
		<< setw(15) << "Prison ID"
		<< setw(15) << "Murderer"
		<< setw(15) << "Number of crimes\n";

	for (int i = 0; i < prison.numberOfPrisoners; ++i)
		tabulatePrisonerData(prison.prisoners[i]);

	cout << "--------------------\n";
}

bool prisonID_comparator(Prisoner const* p1, Prisoner const* p2)
{
	return p1->prisonID < p2->prisonID;
}

bool numberOfCrimes_comparator(Prisoner const* p1, Prisoner const* p2)
{
	return p1->numberOfCrimes >= p2->numberOfCrimes;
}

using Comparator = bool(*)(Prisoner const*, Prisoner const*);

// selection sort
void sortPrisoners(Prisoner* prisoners[], int n, Comparator comp)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (comp(prisoners[j], prisoners[minIndex]))
				minIndex = j;
		}

		swap(prisoners[minIndex], prisoners[i]);
	}
}

void tabulateSortedData(Prisoner* prisoners[], int n)
{
	for (int i = 0; i < n; ++i)
		tabulatePrisonerData(*prisoners[i]);
}

void testReadingData()
{
	Prison prison;
	readPrisonData(prison);
	tabulatePrisonData(prison);
}

int main()
{
	// testReadingData();

	Prison prison{ "FoxRiver", "Henry Pope", 3 };

	prison.prisoners[0] = { "Michael Scofield", 12345, false, 1 };
	prison.prisoners[1] = { "Lincoln Burrows", 54321, true, 2 };
	prison.prisoners[2] = { "John Abruzzi", 30523, true, 5 };

	tabulatePrisonData(prison);

	Prisoner* ptrs[3];
	ptrs[0] = &prison.prisoners[0];
	ptrs[1] = &prison.prisoners[1];
	ptrs[2] = &prison.prisoners[2];

	sortPrisoners(ptrs, 3, prisonID_comparator);
	cout << "\nPrisoner's data sorted by prison ID\n";
	tabulateSortedData(ptrs, 3);

	sortPrisoners(ptrs, 3, numberOfCrimes_comparator);
	cout << "\nPrisoner's data sorted by number of crimes\n";
	tabulateSortedData(ptrs, 3);

	return 0;
}
