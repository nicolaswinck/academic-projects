#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "ConfirmOrder.h"

using namespace std;

ConfirmOrder::ConfirmOrder()
{
	m_toys = nullptr;
	m_numOfToys = 0;
}

ConfirmOrder::~ConfirmOrder()
{
	if (m_toys)
	{
		delete[] m_toys;
		m_toys = nullptr;
	}
}

ConfirmOrder::ConfirmOrder(const ConfirmOrder& rho)
{
	// Copying the righthand object to this.
	m_numOfToys = rho.m_numOfToys;
	// Creating new array with the argument length.
	m_toys = new const Toy * [m_numOfToys];
	// Allocating the space (new Toy objects).
	for (size_t i = 0; i < m_numOfToys; i++)
	{
		m_toys[i] = rho.m_toys[i];
	}
}

ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& rho)
{
	// Checking for self-assignment.
	if (this != &rho)
	{
		// Deallocating memory for the array.
		if (m_toys)
		{
			delete[] m_toys;
			m_toys = nullptr;
		}

		m_numOfToys = rho.m_numOfToys;
		m_toys = new const Toy * [m_numOfToys];

		for (size_t i = 0; i < m_numOfToys; ++i)
		{
			m_toys[i] = rho.m_toys[i];
		}
	}

	return *this;
}

ConfirmOrder::ConfirmOrder(ConfirmOrder&& rho) noexcept
{
	// Copying all the attributes.
	m_toys = rho.m_toys;
	m_numOfToys = rho.m_numOfToys;
	// Deleting the previous object (moving).
	rho.m_toys = nullptr;
	rho.m_numOfToys = 0;
}

ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& rho) noexcept
{
	if (this != &rho)
	{
		if (m_toys)
		{
			delete[] m_toys;
			m_toys = nullptr;
		}

		m_toys = rho.m_toys;
		m_numOfToys = rho.m_numOfToys;

		rho.m_toys = nullptr;
		rho.m_numOfToys = 0u;
	}

	return *this;
}

ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy)
{
	// Flag for checking the presence of a toy in the array.
	bool result = false;

	for (size_t i = 0; i < m_numOfToys && !result; i++)
	{
		// Setting true if toys match.
		if (m_toys[i] == &toy)
		{
			result = true;
		}
	}
	// Case where there's no address of argument toy in the array.
	if (!result)
	{
		// Creating temporary toy and resizing the array (add one slot).
		const Toy** tempToy = new const Toy * [m_numOfToys + 1];

		// Adding.
		for (size_t i = 0; i < m_numOfToys; i++)
		{
			tempToy[i] = m_toys[i];
		}
		// Passing the argument toy..
		tempToy[m_numOfToys] = &toy;
		// Safely deallocating memory.
		if (m_toys)
		{
			delete[] m_toys;
			m_toys = nullptr;
		}
		// Updating.
		m_toys = tempToy;
		m_numOfToys++;
	}

	return *this;
}

ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy)
{
	// Setting a counter.
	size_t addressCount = 0;

	for (size_t i = 0; i < m_numOfToys; i++)
	{
		if (m_toys[i] == &toy)
		{
			m_toys[i] = nullptr;
			addressCount++;
		}
	}
	// Case where there's at least one corresponding address in the array.
	if (addressCount > 0)
	{
		// Creating temporary toy and resizing the array (remove the addresses pointed).
		const Toy** tempToy = new const Toy * [m_numOfToys - addressCount];

		for (size_t i = 0, j = 0; i < m_numOfToys; i++)
		{
			// Resetting the index.
			if (m_toys[i])
			{
				tempToy[j++] = m_toys[i];
			}
		}

		if (m_toys)
		{
			delete[] m_toys;
			m_toys = nullptr;
		}
		// Updating.
		m_numOfToys -= addressCount;
		m_toys = tempToy;

	}

	return *this;
}

std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& confOrd)
{
	// Printing out the confirmations label.
	ostr << "--------------------------" << std::endl;
	ostr << "Confirmations to Send" << std::endl;
	ostr << "--------------------------" << std::endl;
	// There are toys to confirm.
	if (confOrd.m_numOfToys > 0)
	{
		for (size_t i = 0; i < confOrd.m_numOfToys; i++)
		{
			ostr << *confOrd.m_toys[i];
		}
	}
	// There are no toys to confirm.
	else
	{
		ostr << "There are no confirmations to send!" << std::endl;
	}

	ostr << "--------------------------" << std::endl;

	return ostr;
}