#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <string>
#include "Container.h"

using namespace std;

void Container::setEmpty()
{
	m_content[0] = '\0';
	m_capacity = 0;
	m_volume = 0;
}

int Container::capacity() const
{
	return m_capacity;
}

int Container::volume() const
{
	return m_volume;
}

Container::Container(const char* content, int capacity, int volume)
{
	if (content && capacity)
	{
		// Setting the attributes with arguments.
		strcpy(m_content, content);
		m_capacity = capacity;
		// Initializing volume to zero.
		m_volume = 0;

		if (volume)
		{
			// Setting volume (if argument is given).
			m_volume = volume;
		}
	}
	else if (content == nullptr || volume > capacity)
	{
		setEmpty();
	}
}

int Container::operator+=(int rhVolume)
{
	// Variable which will hold the added amount (to be returned).
	int added = 0;
	// Calculating a non-exceeding scenario.
	if ((rhVolume + m_volume) <= m_capacity)
	{
		m_volume += rhVolume;
		added = rhVolume;
	}
	// Calculating the exceeding scenario.
	else
	{
		added = m_capacity - rhVolume;
		m_volume = m_capacity;
	}

	return added;
}

int Container::operator-=(int rhVolume)
{
	// Variable which will hold and decrease the reduced amount (to be returned).
	int reduced = 0;
	// Calculating non-exceeding scenario.
	if (m_volume - rhVolume >= 0)
	{
		m_volume -= rhVolume;
		reduced = rhVolume;
	}
	// Calculating exceeding scenario.
	else
	{
		reduced = m_volume;
		m_volume = 0;
	}

	return reduced;
}

Container::operator bool() const
{
	// True container: there's description and volume is under capacity.
	return m_content[0] != '\0' && m_volume <= m_capacity;
}

void Container::clear(int capacity, const char* content)
{
	// Emptying a non-valid container.
	if (content == nullptr || capacity < 0)
	{
		setEmpty();
	}
	// Resetting a valid container.
	else
	{
		m_capacity = capacity;
		strcpy(m_content, content);
		m_volume = 0;
	}
}

std::ostream& Container::print(std::ostream& ostr) const
{
	// Printing a valid container.
	if (*this)
	{
		ostr << m_content << ": (" << m_volume << "cc/" << m_capacity << ')';
	}
	// Printing an invalid container template.
	else
	{
		ostr << "****: (**cc/***)";
	}

	return ostr;
}

std::istream& Container::read(std::istream& istr)
{
	bool inputOk = false;
	int value{};
	int added{};

	if (!*this)
	{
		while (!inputOk)
		{
			// Getting input for the broken/invalid container (newline).
			std::cerr << "Broken Container, adding aborted! Press <ENTER> to continue....";
			char c = istr.get();

			if (c == '\n')
			{
				inputOk = true;
			}

			istr.ignore(10000, '\n');
		}
	}
	else
	{
		// Getting input for the valid container.
		std::cout << "Add to ";
		print(std::cout) << std::endl;
		std::cout << "> ";
		istr >> value;
		// Setting the condition for fail and large inputs.
		while (value < 1 || value > 220000)
		{
			if (istr.fail())
			{
				std::cerr << "Invalid Integer, retry: ";
			}
			else
			{
				std::cerr << "Value out of range [1<=val<=" << m_capacity - m_volume << "]: ";
			}

			istr.clear();
			istr.ignore(10000, '\n');
		}
		// Grabbing the added value.
		added = *this += value;
		// Printing added cubic centimeters.
		std::cout << "Added " << added << " CCs" << std::endl;
	}

	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const Container& con)
{
	return con.print(ostr);
}

std::istream& operator>>(std::istream& istr, Container& con)
{
	return con.read(istr);
}