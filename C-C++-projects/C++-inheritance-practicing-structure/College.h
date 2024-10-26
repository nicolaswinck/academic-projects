#ifndef COLLEGE_H
#define COLLEGE_H

#include <iostream>
#include <vector>
#include <list>
#include "Person.h"

class College
{
	std::vector<Person*> m_persons;

public:
	// Default constructor.
	College() = default;
	// Copies disabled.
	College(const College&) = delete;
	College& operator=(const College&) = delete;
	College& operator +=(Person* thePerson);
	void display(std::ostream& out) const;
	~College();
	// Template function.
	template<typename T>
	void select(const T& test, std::list<const Person*>& persons);
};

template<typename T>
void College::select(const T& test, std::list<const Person*>& persons)
{
	for (const Person* person : m_persons)
	{
		// Testing each person object.
		if (test(person))
		{
			persons.push_back(person);
		}
	}
}

#endif