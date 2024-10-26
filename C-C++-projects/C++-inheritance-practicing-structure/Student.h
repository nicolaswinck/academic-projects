#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include "Person.h"

class Student : public Person
{
	std::string m_name{ "" };
	int m_age{ 0 };
	std::string m_id{ "" };
	std::vector<std::string> m_courses;
	size_t m_count{ 0u };

public:
	// Default constructor.
	Student() = default;
	Student(std::istream& istr);
	// Copies disabled.
	Student(const Student&) = delete;
	Student& operator=(const Student&) = delete;
	std::string status() const;
	std::string name() const;
	std::string id() const;
	std::string age() const;
	void display(std::ostream& out) const;
	// Trimming utility.
	std::string trim(std::string token);
};

#endif