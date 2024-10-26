#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

// Initializing class variables (unsigned).
size_t Station::m_widthField = 0u;
size_t Station::id_generator = 0u;

Station::Station(const std::string& line)
{
	// Creating Utility temp object for extraction.
	Utilities temp;
	// Position and boolean flag for contiune extraction.
	size_t pos = 0u;
	bool more = true;

	// Pre-incrementing ID for new instance of Station from 1.
	m_id = ++Station::id_generator;

	// Tokenizing to temp object.
	m_itemName = temp.extractToken(line, pos, more);
	m_serial = stoi(temp.extractToken(line, pos, more));
	m_qty = stoi(temp.extractToken(line, pos, more));

	// Updating width.
	if (temp.getFieldWidth() > Station::m_widthField)
	{
		Station::m_widthField = temp.getFieldWidth();
	}

	// Getting description.
	m_descr = temp.extractToken(line, pos, more);
}

const std::string& Station::getItemName() const
{
	return m_itemName;
}

size_t Station::getNextSerialNumber()
{
	// Incrementing serial number.
	m_serial++;

	return m_serial - 1;
}

size_t Station::getQuantity() const
{
	return m_qty;
}

void Station::updateQuantity()
{
	// Being sure quantity is positive.
	if (m_qty > 0)
	{
		m_qty -= 1;
	}
}

void Station::display(std::ostream& os, bool full) const
{
	// Displaying information (adding padded zeros to ID and serial).
	os << right << setfill('0') << setw(3) << m_id << " | ";
	os << left << setfill(' ') << setw(m_widthField) << m_itemName << " | ";
	os << right << setfill('0') << setw(6) << m_serial << " | ";

	if (full)
	{
		os << right << setfill(' ') << setw(4) << m_qty << " | ";
		os << left << m_descr;
	}

	// Ending line.
	os << endl;
}