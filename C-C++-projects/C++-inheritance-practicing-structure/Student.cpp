#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Student.h"

using namespace std;

Student::Student(std::istream& istr)
{
	// Variables to hold temp attributes.
	string record;
	string tempTag;
	string tempAge;
	string tempCount;
	// Validation flags for age and m_courses size.
	bool ageValid = true;
	bool countValid = true;

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

	// Checking ID (not empty, starts with S).
	if (m_id.empty() || m_id[0] != 'S')
	{
		throw runtime_error(m_name + "++Invalid record!");
	}

	getline(istr, record, ',');
	tempCount = trim(record);

	// Checking if counter is a number.
	for (size_t i = 0; i < tempCount.length() && countValid; i++)
	{
		if (!isdigit(tempCount[i]))
		{
			countValid = false;
		}
	}

	if (!countValid)
	{
		throw runtime_error(m_name + "++Invalid record!");
	}

	m_count = stoi(tempCount);

	// Tokenizing courses from the vector.
	for (size_t i = 0; i < m_count; i++)
	{
		string course;
		getline(istr, course, ',');

		m_courses.push_back(trim(course));
	}
}

std::string Student::status() const
{
	return "Student";
}

std::string seneca::Student::name() const
{
	return m_name;
}

void Student::display(std::ostream& out) const
{
	out << "| ";
	out << left << setw(10) << status() << "| ";
	out << left << setw(10) << id() << "| ";
	out << left << setw(20) << name() << " | ";
	out << left << setw(3) << age() << " |";

	// Managing comma placement for the courses.
	for (size_t i = 0; i < m_count; i++)
	{
		if (i == m_count - 1)
		{
			out << m_courses[i];
		}
		else
		{
			out << m_courses[i] << ", ";
		}
	}
}

std::string Student::id() const
{
	return m_id;
}

std::string Student::age() const
{
	return to_string(m_age);
}

std::string Student::trim(std::string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}