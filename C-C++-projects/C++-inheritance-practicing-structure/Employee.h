#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "Person.h"

class Employee : public Person
{
	std::string m_name{ "" };
	int m_age{ 0 };
	std::string m_id{ "" };

public:
	// Default constructor.
	Employee() = default;
	Employee(std::istream& istr);
	std::string status() const;
	std::string name() const;
	std::string id() const;
	std::string age() const;
	void display(std::ostream& out) const;
	// Trimming utility.
	std::string trim(std::string token);
};

#endif