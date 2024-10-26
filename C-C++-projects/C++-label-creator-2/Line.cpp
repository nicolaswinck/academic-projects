#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "Line.h"

using namespace std;

Line::Line() : LblShape()
{
	m_length = 0;
}
// Two-argument constructor using the base class constructor to set the label.
Line::Line(const char* label, int length) : LblShape(label)
{
	m_length = length;
}

void Line::getSpecs(std::istream& istr)
{
	// Getting specs from the base class.
	LblShape::getSpecs(istr);
	// Reading value of m_length to istr.
	istr >> m_length;
	// Ignoring enough characters up to newline char.
	istr.ignore(1000, '\n');
}

void Line::draw(std::ostream& ostr) const
{
	if (m_length > 0 && label() != nullptr)
	{
		// Printing the label and filling out the line.
		ostr << label() << endl;
		ostr.width(m_length);
		ostr.fill('=');
		ostr << '=';
	}
}