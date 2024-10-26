#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <vector>
#include "Employee.h"

class Professor : public Employee
{
	std::string m_department{ "" };

public:
	Professor(std::istream& in);
	void display(std::ostream& out) const;
	std::string status() const;
	std::string department() const;
};

#endif