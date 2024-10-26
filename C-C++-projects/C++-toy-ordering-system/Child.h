#ifndef CHILD_H
#define CHILD_H

#include <cstring>
#include <iostream>
#include "Toy.h"

class Child
{
	// Name and age for the child.
	std::string m_name;
	int m_age;
	// Array and array size.
	const Toy** m_toys;
	size_t m_numOfToys;

public:
	// Default constructor.
	Child();
	Child(std::string name, int age, const Toy* toys[], size_t count);
	// Destructor.
	~Child();
	// Copy constructor.
	Child(const Child& rhc);
	// Copy assignment operator.
	Child& operator=(const Child& rhc);
	size_t size() const;
	// Move constructor.
	Child(Child&& rhc) noexcept;
	// Move assignment operator.
	Child& operator=(Child&& rhc) noexcept;
	// Insertion operator (overload).
	friend std::ostream& operator<<(std::ostream& ostr, const Child& child);
};

#endif