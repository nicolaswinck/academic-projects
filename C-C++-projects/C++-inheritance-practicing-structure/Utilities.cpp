#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <sstream>
#include "Employee.h"
#include "Student.h"
#include "Professor.h"
#include "Utilities.h"

using namespace std;

Person* buildInstance(std::istream& in)
{
	// Setting a holder for the result.
	Person* result = nullptr;
	// Getting instr to a string and storing first character.
	string record;
	getline(in, record);
	char ch = record[0];

	// Checking if the istr is not empty.
	if (!record.empty())
	{
		// Creating new instances according to the tag.
		if (ch == 'e' || ch == 'E')
		{
			stringstream ss(record);
			result = new Employee(ss);
		}
		else if (ch == 'p' || ch == 'P')
		{
			stringstream ss(record);
			result = new Professor(ss);
		}
		else if (ch == 's' || ch == 'S')
		{
			stringstream ss(record);
			result = new Student(ss);
		}
	}

	return result;
}