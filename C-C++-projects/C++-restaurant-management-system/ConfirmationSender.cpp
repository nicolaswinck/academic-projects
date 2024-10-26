#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <string>
#include "ConfirmationSender.h"
#include "Reservation.h"

using namespace std;

ConfirmationSender::ConfirmationSender() : m_reservations(nullptr), m_numOfReservations(0) {}

ConfirmationSender::ConfirmationSender(const ConfirmationSender& rhcs)
{
	// Assigning the other object (right) to this.
	m_numOfReservations = rhcs.m_numOfReservations;
	m_reservations = rhcs.m_reservations;

	// Checking for empty object (it will to nothing).
	if (rhcs.m_reservations != nullptr)
	{
		// Allocating memory for the copies of the reservations.
		m_reservations = new const Reservation * [m_numOfReservations];

		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			m_reservations[i] = rhcs.m_reservations[i];
		}
	}
}

ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& rhcs)
{
	// Checking for self-assignment.
	if (this != &rhcs)
	{
		// Allocating memory for each element.
		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			delete m_reservations[i];
			m_reservations[i] = nullptr;
		}

		delete[] m_reservations;
		m_reservations = nullptr;

		m_numOfReservations = rhcs.m_numOfReservations;
		m_reservations = new const Reservation * [m_numOfReservations];

		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			m_reservations[i] = rhcs.m_reservations[i];
		}
	}
	return *this;
}

ConfirmationSender::ConfirmationSender(ConfirmationSender&& rhcs) noexcept
{
	// Assigning other object (right) to this.
	m_numOfReservations = rhcs.m_numOfReservations;
	m_reservations = rhcs.m_reservations;

	// Deallocating other object (right).
	rhcs.m_reservations = nullptr;
	rhcs.m_numOfReservations = 0;
}

ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& rhcs) noexcept
{
	if (this != &rhcs)
	{
		delete[] m_reservations;
		m_reservations = nullptr;

		m_reservations = rhcs.m_reservations;
		m_numOfReservations = rhcs.m_numOfReservations;

		rhcs.m_reservations = nullptr;
		rhcs.m_numOfReservations = 0;
	}

	return *this;
}

ConfirmationSender::~ConfirmationSender()
{
	delete[] m_reservations;
	m_reservations = nullptr;
}

ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res)
{
	// Boolean flag to identify object found in the array.
	bool resFound = false;

	// Going over each reservation.
	for (size_t i = 0u; i < m_numOfReservations; i++)
	{
		// Checking for a match with the other object's address.
		if (m_reservations[i] == &res)
		{
			resFound = true;
		}
	}

	// Case for object not found.
	if (!resFound)
	{
		// Allocating memory for a new array with extra space for the object.
		const Reservation** newReservations = new const Reservation * [m_numOfReservations + 1];

		// Assigning elements to new array.
		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			newReservations[i] = m_reservations[i];
		}

		// Assigning new object.
		newReservations[m_numOfReservations] = &res;

		// Deallocating previous array.
		delete[] m_reservations;
		m_reservations = nullptr;

		// Resizing.
		m_reservations = newReservations;
		m_numOfReservations++;
	}

	return *this;
}

ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
{
	// Boolean flag to identify object found in the array.
	bool resFound = false;

	for (size_t i = 0u; i < m_numOfReservations && !resFound; i++)
	{
		if (m_reservations[i] == &res)
		{
			m_reservations[i] = nullptr;
			resFound = true;
		}
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const ConfirmationSender& conf)
{
	os << "--------------------------" << endl;
	os << "Confirmations to Send" << endl;
	os << "--------------------------" << endl;

	if (conf.m_numOfReservations > 0)
	{
		for (size_t i = 0u; i < conf.m_numOfReservations; i++)
		{
			if (conf.m_reservations[i] != nullptr)
			{
				os << *conf.m_reservations[i];
			}
		}
	}
	else
	{
		os << "There are no confirmations to send!" << endl;
	}

	os << "--------------------------" << endl;

	return os;
}