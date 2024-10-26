#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "Rectangle.h"

using namespace std;

// No-argument constructor invoking default constructor from base class.
Rectangle::Rectangle() : LblShape()
{
	m_width = 0;
	m_height = 0;
}
// Three-argument constructor passing the label to the base class constructor.
Rectangle::Rectangle(const char* label, int width, int height)
	: LblShape(label)
{
	// Setting width and height.
	m_width = width;
	m_height = height;
	// Casting unsigned strlen value (unsigned int) to int.
	if (m_height < 3 || m_width < (int)strlen(label) + 2)
	{
		// Setting rectangle to empty state.
		m_width = 0;
		m_height = 0;
	}
}

void Rectangle::getSpecs(std::istream& istr)
{
	// Creating comma separator.
	char comma;
	// Getting the specs from the base class.
	LblShape::getSpecs(istr);
	// Reading two comma-separated values from istr.
	istr >> m_width >> comma >> m_height;
	// Ignoring enough characters up to newline char.
	istr.ignore(10000, '\n');
}

void Rectangle::draw(std::ostream& ostr) const
{
	if (label() != nullptr && m_width > 0 && m_height > 0)
	{
		// First line.
		ostr << '+';
		ostr.width(m_width - 2);
		ostr.fill('-');
		ostr << '-' << '+' << endl;
		// Second line.
		ostr << '|';
		ostr.width(m_width - 2);
		ostr.setf(ios::left);
		ostr.fill(' ');
		ostr << label() << '|' << endl;
		// Third and fourth lines (using m_height - 3).
		for (int i = 0; i < (m_height - 3); i++)
		{
			ostr << '|';
			ostr.width(m_width - 2);
			ostr.fill(' ');
			ostr << ' ' << '|' << endl;
		}
		// Last line.
		ostr << '+';
		ostr.width(m_width - 2);
		ostr.fill('-');
		ostr << '-' << '+';
	}
}