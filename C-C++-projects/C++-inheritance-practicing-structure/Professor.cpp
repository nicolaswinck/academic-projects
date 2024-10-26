#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Professor.h"

using namespace std;

Professor::Professor(std::istream& in)
	: Employee(in) // Calling constructor for Employee.
{
	// Tokenizing record (remaining in the istr).
	string record;
	getline(in, record);

	m_department = trim(record);
}

void Professor::display(std::ostream& out) const
{
	// Calling display() from Employee and adding the rest.
	Employee::display(out);

	out << department() << "| " << "Professor";
}

std::string Professor::status() const
{
	return "Professor";
}

std::string Professor::department() const
{
	return m_department;
}