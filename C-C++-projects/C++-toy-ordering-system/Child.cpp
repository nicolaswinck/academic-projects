#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Child.h"

using namespace std;

Child::Child()
{
	m_name = {};
	m_age = 0;
	m_numOfToys = 0;
	m_toys = nullptr;
}

Child::Child(string name, int age, const Toy* toys[], size_t count)
{
	// Copying the arguments to the attributes.
	m_name = name;
	m_age = age;
	// Creating new array with the argument length.
	m_toys = new const Toy * [count];
	m_numOfToys = count;
	// Allocating the space (new Toy objects).
	for (size_t i = 0; i < count; i++)
	{
		m_toys[i] = new Toy(*toys[i]);
	}
}

Child::Child(const Child& rhc)
{
	// Copying righthand objects to this.
	m_name = rhc.m_name;
	m_age = rhc.m_age;
	m_numOfToys = rhc.m_numOfToys;
	m_toys = new const Toy * [m_numOfToys];

	for (size_t i = 0; i < m_numOfToys; i++)
	{
		m_toys[i] = new Toy(*rhc.m_toys[i]);
	}
}

Child& Child::operator=(const Child& rhc)
{
	// Checking for self-assignment.
	if (this != &rhc)
	{
		// Deallocating memory for all the elements of the array.
		for (size_t i = 0; i < m_numOfToys; i++)
		{
			delete m_toys[i];
		}
		// Deallocating memory for the array.
		delete[] m_toys;
		m_toys = nullptr;

		m_name = rhc.m_name;
		m_age = rhc.m_age;
		m_numOfToys = rhc.m_numOfToys;
		m_toys = new const Toy * [m_numOfToys];

		for (size_t i = 0; i < m_numOfToys; i++)
		{
			m_toys[i] = new Toy(*rhc.m_toys[i]);
		}
	}

	return *this;
}

Child::~Child()
{
	// Safely deallocating memory for each element and the whole array.
	if (m_toys)
	{
		for (size_t i = 0; i < m_numOfToys; i++)
		{
			delete m_toys[i];
		}

		delete[] m_toys;
		m_toys = nullptr;
	}
}

size_t Child::size() const
{
	return m_numOfToys;
}

Child::Child(Child&& rhc) noexcept
{
	// Copying all the attributes.
	m_name = rhc.m_name;
	m_age = rhc.m_age;
	m_numOfToys = rhc.m_numOfToys;
	m_toys = rhc.m_toys;
	// Deleting the previous object (moving).
	rhc.m_name = {};
	rhc.m_age = 0;
	rhc.m_numOfToys = 0;
	rhc.m_toys = nullptr;
}

Child& Child::operator=(Child&& rhc) noexcept
{
	if (this != &rhc)
	{
		for (size_t i = 0; i < m_numOfToys; i++)
		{
			delete m_toys[i];
		}

		delete[] m_toys;
		m_toys = nullptr;

		m_name = rhc.m_name;
		m_age = rhc.m_age;
		m_numOfToys = rhc.m_numOfToys;
		m_toys = rhc.m_toys;

		rhc.m_name = {};
		rhc.m_age = 0;
		rhc.m_numOfToys = 0;
		rhc.m_toys = nullptr;
	}

	return *this;
}

ostream& operator<<(ostream& ostr, const Child& child)
{
	// Creating a static counter as per documentation.
	static int CALL_CNT = 0;
	// Incrementing to count the calls to this operator.
	CALL_CNT++;

	// Printing the display for the child.
	ostr << "--------------------------" << endl;
	ostr << "Child " << CALL_CNT << ": "
		<< child.m_name << ' ' << child.m_age << " years old:" << endl;
	ostr << "--------------------------" << endl;

	// There are toys in the array.
	if (child.m_numOfToys > 0)
	{
		for (size_t i = 0; i < child.m_numOfToys; i++)
		{
			ostr << *child.m_toys[i];
		}
	}
	// There are no toys in the array.
	else
	{
		ostr << "This child has no toys!" << endl;
	}

	ostr << "--------------------------" << endl;

	return ostr;
}