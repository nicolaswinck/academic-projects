#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "College.h"

using namespace std;

College& College::operator+=(Person* thePerson)
{
	// Adding the argument person to the end of the vector.
	m_persons.push_back(thePerson);

	return *this;
}

void College::display(std::ostream& out) const
{
	// Labels copied directly from the sample output provided.
	out << "------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "|                                        Test #1 Persons in the college!                                               |" << endl;
	out << "------------------------------------------------------------------------------------------------------------------------" << endl;

	// Iterating over the vector.
	for (const auto& person : m_persons)
	{
		person->display(out);
		out << std::endl;
	}

	out << "------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "|                                        Test #2 Persons in the college!                                               |" << endl;
	out << "------------------------------------------------------------------------------------------------------------------------" << endl;

	// Manually displaying with the public person queries.
	for (const auto& person : m_persons)
	{
		out << "| ";
		out << left << setw(10) << person->status() << "| ";
		out << left << setw(10) << person->id() << "| ";
		out << left << setw(20) << person->name() << " | ";
		out << left << setw(3) << person->age() << " |";
		out << endl;
	}

	out << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

College::~College()
{
	for (Person* person : m_persons)
	{
		delete person;
	}
}