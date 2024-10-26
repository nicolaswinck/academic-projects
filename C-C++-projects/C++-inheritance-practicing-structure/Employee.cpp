#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Employee.h"

using namespace std;

Employee::Employee(std::istream& istr)
{
	// Variables to hold temp attributes from istr.
	string record;
	string tempTag;
	string tempAge;
	// Age validation flag.
	bool ageValid = true;

	// Getting attributes and trimming spaces.
	getline(istr, record, ',');
	tempTag = trim(record);

	getline(istr, record, ',');
	m_name = trim(record);

	getline(istr, record, ',');
	tempAge = trim(record);

	// Checking if age is a number.
	for (size_t i = 0; i < tempAge.length() && ageValid; i++)
	{
		if (!isdigit(tempAge[i]))
		{
			ageValid = false;
		}
	}

	if (!ageValid)
	{
		throw runtime_error(m_name + "++Invalid record!");
	}

	m_age = stoi(tempAge);

	getline(istr, record, ',');
	m_id = trim(record);

	// Checking ID (not empty, starts with E).
	if (m_id.empty() || m_id[0] != 'E')
	{
		throw runtime_error(m_name + "++Invalid record!");
	}
}

std::string Employee::status() const
{
	return "Employee";
}

std::string Employee::name() const
{
	return m_name;
}

std::string Employee::id() const
{
	return m_id;
}

std::string Employee::age() const
{
	return to_string(m_age);
}

void Employee::display(std::ostream& out) const
{
	out << "| ";
	out << left << setw(10) << "Employee" << "| ";
	out << left << setw(10) << id() << "| ";
	out << left << setw(20) << name() << " | ";
	out << left << setw(3) << age() << " |";
}

std::string Employee::trim(std::string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}