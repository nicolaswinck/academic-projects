#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <string>
#include "Restaurant.h"
#include "Reservation.h"

using namespace std;

Restaurant::Restaurant() : m_reservations(nullptr), m_numOfReservations(0) {}

// Initialization list: default constructor.
Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : Restaurant()
{
	// If the object is empty, it will do nothing.
	if (cnt > 0)
	{
		// Assigning the argument to the number of reservations.
		m_numOfReservations = cnt;
		// Allocating memory for the copies of the reservations.
		m_reservations = new const Reservation * [cnt];

		// Assigning elements.
		for (size_t i = 0u; i < cnt; i++)
		{
			m_reservations[i] = new Reservation(*reservations[i]);
		}
	}
}

// Initialization list: default constructor.
Restaurant::Restaurant(const Restaurant& rhr) : Restaurant()
{
	// If the object is empty, it will do nothing.
	if (rhr.m_numOfReservations > 0)
	{
		// Assigning the right hand # of reservations to this.
		m_numOfReservations = rhr.m_numOfReservations;
		// Allocating memory for the copies of the reservations.
		m_reservations = new const Reservation * [m_numOfReservations];

		// Assigning elements.
		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			m_reservations[i] = new Reservation(*rhr.m_reservations[i]);
		}
	}
}

Restaurant& Restaurant::operator=(const Restaurant& rhr)
{
	// Checking for self-assignment.
	if (this != &rhr)
	{
		// Allocating memory for each element.
		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			delete m_reservations[i];
			m_reservations[i] = nullptr;
		}

		delete[] m_reservations;
		m_reservations = nullptr;

		m_numOfReservations = rhr.m_numOfReservations;
		m_reservations = new const Reservation * [m_numOfReservations];

		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			m_reservations[i] = new Reservation(*rhr.m_reservations[i]);
		}
	}

	return *this;
}

Restaurant::Restaurant(Restaurant&& rhr) noexcept
{
	// Assigning other object (right) to this.
	m_reservations = rhr.m_reservations;
	m_numOfReservations = rhr.m_numOfReservations;

	// Deallocating other object (right).
	rhr.m_reservations = nullptr;
	rhr.m_numOfReservations = 0;
}

Restaurant& Restaurant::operator=(Restaurant&& rhr) noexcept
{
	if (this != &rhr)
	{
		for (size_t i = 0; i < m_numOfReservations; i++)
		{
			delete m_reservations[i];
			m_reservations[i] = nullptr;
		}

		delete[] m_reservations;
		m_reservations = nullptr;

		m_reservations = rhr.m_reservations;
		m_numOfReservations = rhr.m_numOfReservations;

		rhr.m_reservations = nullptr;
		rhr.m_numOfReservations = 0;
	}

	return *this;
}

Restaurant::~Restaurant()
{
	for (size_t i = 0; i < m_numOfReservations; i++)
	{
		delete m_reservations[i];
		m_reservations[i] = nullptr;
	}

	delete[] m_reservations;
	m_reservations = nullptr;
}

size_t Restaurant::size() const
{
	return m_numOfReservations;
}

std::ostream& operator<<(std::ostream& os, const Restaurant& rest)
{
	// Setting the counter for this function (starting from 1).
	static int count = 1;

	os << "--------------------------" << endl;
	os << "Fancy Restaurant (" << count++ << ')' << endl;
	os << "--------------------------" << endl;

	if (rest.size() > 0)
	{
		for (size_t i = 0u; i < rest.size(); i++)
		{
			if (rest.m_reservations[i] != nullptr)
			{
				os << *rest.m_reservations[i];
			}
		}
	}
	else
	{
		os << "This restaurant is empty!" << endl;
	}

	os << "--------------------------" << endl;

	return os;
}