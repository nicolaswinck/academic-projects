#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;

std::deque<CustomerOrder> g_pending;
std::deque<CustomerOrder> g_completed;
std::deque<CustomerOrder> g_incomplete;

Workstation::Workstation(const string& line) : Station{ line } {}

void Workstation::fill(std::ostream& os)
{
	if (!m_orders.empty())
	{
		m_orders.front().fillItem(*this, os);
	}
}

bool Workstation::attemptToMoveOrder()
{
	// Boolean flag for moving order (presuming false).
	bool result = false;

	// Case for no orders (move).
	if (m_orders.empty())
	{
		result = true;
	}
	else
	{
		// Case for no more service required or not enough inventory (move).
		if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0)
		{
			// Case for no next station in assembly line (move to complete or incomplete).
			if (m_pNextStation == nullptr)
			{

				if (m_orders.front().isOrderFilled())
				{
					g_completed.emplace_back(move(m_orders.front()));
				}
				else
				{
					g_incomplete.emplace_back(move(m_orders.front()));
				}
			}
			// There is a next station.
			else
			{
				(*m_pNextStation) += move(m_orders.front());
			}

			// Updating m_orders (move).
			m_orders.pop_front();
			result = true;
		}

		result = false;
	}

	return result;
}

void Workstation::setNextStation(Workstation* station)
{
	m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}

void Workstation::display(std::ostream& os) const
{
	os << getItemName() << " --> ";

	if (m_pNextStation)
	{
		os << m_pNextStation->getItemName();
	}
	else
	{
		os << "End of Line";
	}

	os << endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
{
	m_orders.push_back(move(newOrder));

	return *this;
}