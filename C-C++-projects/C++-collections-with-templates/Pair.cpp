#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include "Pair.h"

using namespace std;

Pair::Pair()
{
	m_key = {};
	m_value = {};
}

Pair::Pair(const Pair& rhp)
{
	// Copying right object to this object.
	m_key = rhp.m_key;
	m_value = rhp.m_value;
}

Pair& Pair::operator=(const Pair& rhp)
{
	// Checking for self-assignment.
	if (this != &rhp)
	{
		m_key = rhp.m_key;
		m_value = rhp.m_value;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Pair& rhp)
{
	// Formatting as per example output.
	ostr << std::setw(20) << std::right;
	// Printing out the key and the value.
	ostr << rhp.m_key << ": " << rhp.m_value;

	return ostr;
}

bool operator==(const Pair& lhp, const Pair& rhp)
{
	// Yields true if either the key or the value is equal to the righthand object.
	return (lhp.m_key == rhp.m_key) || (lhp.m_value == rhp.m_value);
}