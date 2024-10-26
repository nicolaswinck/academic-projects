#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include "HealthInfo.h"

using namespace std;

bool HealthCard::validID(const char* name, long long number, const char vCode[], const char sNumber[]) const
{
	// Validating data members.
	return (name != nullptr && strlen(name))
		&& (number > 999999999 && number < 9999999999)
		&& strlen(vCode) == 2
		&& strlen(sNumber) == 9;
}

void HealthCard::setEmpty()
{
	delete[] m_name;
	m_name = nullptr;
}

void HealthCard::allocateAndCopy(const char* name)
{
	// Clearing memory space.
	delete[] m_name;
	// Dynamically allocating space.
	m_name = new char[strlen(name) + 1];
	// Copying the argument to the data member.
	strcpy(m_name, name);
}

void HealthCard::extractChar(std::istream& istr, char ch) const
{
	// Peeking next character.
	if (istr.peek() == ch)
	{
		// Ignoring character.
		istr.ignore();
	}
	else
	{
		istr.ignore(1000, ch);
		istr.setstate(ios::failbit);
	}
}

std::ostream& HealthCard::printIDInfo(std::ostream& ostr) const
{
	ostr << m_number << '-' << m_vCode << ", " << m_sNumber;

	return ostr;
}

void HealthCard::set(const char* name, long long number, const char vCode[], const char sNumber[])
{
	if (validID(name, number, vCode, sNumber))
	{
		// Setting each data member to the argument member.
		allocateAndCopy(name);
		m_number = number;
		strcpy(m_vCode, vCode);
		strcpy(m_sNumber, sNumber);
	}
	else
	{
		// Deleting remaining memory and setting obj. to safe empty state.
		delete[] m_name;
		m_name = nullptr;
		setEmpty();
	}
}

HealthCard::HealthCard(const char* name, long long number, const char vCode[], const char sNumber[])
{
	// Checking for the four-argument-constructor.
	if (name && number && vCode && sNumber)
	{
		// Setting members.
		set(name, number, vCode, sNumber);
	}
	else
	{
		setEmpty();
	}
}

HealthCard::HealthCard(const HealthCard& hc)
{
	// Checking for hc obj. validation.
	if (hc.validID(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber))
	{
		// Setting *this members.
		set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
	}
	else
	{
		setEmpty();
	}
}

HealthCard& HealthCard::operator=(const HealthCard& hc)
{
	// Checking for self-assignment.
	if (this != &hc)
	{
		if (hc.validID(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber))
		{
			set(hc.m_name, hc.m_number, hc.m_vCode, hc.m_sNumber);
		}
		else
		{
			setEmpty();
		}
	}

	return *this;
}

HealthCard::~HealthCard()
{
	delete[] m_name;
}

HealthCard::operator bool() const
{
	return m_name != nullptr;
}

std::ostream& HealthCard::print(std::ostream& ostr, bool toFile) const
{
	// Chacking for valid members.
	if (validID(m_name, m_number, m_vCode, m_sNumber))
	{
		// File flag: print to file.
		if (toFile)
		{
			ostr << m_name << ',';
			printIDInfo(ostr) << endl;
		}
		// Print to screen.
		else
		{
			ostr.fill('.');
			ostr.width(50);
			ostr.setf(ios::left);
			ostr << m_name;
			printIDInfo(ostr);
		}
	}

	return ostr;
}

std::istream& HealthCard::read(std::istream& istr)
{
	// Local variables for each part of the card information.
	char localName[MaxNameLength];
	long long localNumber;
	char localVCode[3];
	char localSNumber[10];
	// Getting each information with the expected format.
	istr.get(localName, MaxNameLength, ',');
	extractChar(istr, ',');
	istr >> localNumber;
	extractChar(istr, '-');
	istr.get(localVCode, 3, ',');
	extractChar(istr, ',');
	istr.get(localSNumber, 10, '\n');
	// Checking for failure state.
	if (istr)
	{
		set(localName, localNumber, localVCode, localSNumber);
	}
	// Clearing and ignoring remaining characters.
	istr.clear();
	istr.ignore(1000, '\n');

	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc)
{
	if (hc)
	{
		// Printing on screen.
		hc.print(ostr, false);
	}
	else
	{
		// Error.
		ostr << "Invalid Health Card Record";
	}

	return ostr;
}

std::istream& operator>>(std::istream& istr, HealthCard& hc)
{
	return hc.read(istr);
}
