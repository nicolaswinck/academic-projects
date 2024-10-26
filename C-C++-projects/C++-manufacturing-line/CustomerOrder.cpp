#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

// Defining class variable.
size_t CustomerOrder::m_widthField = 0u;

CustomerOrder::CustomerOrder(const std::string& line)
{
	// Creating local object.
	Utilities util;

	// Holder for position index and bool flag.
	size_t pos = 0u;
	bool more = true;
	// Temp vector to store the items.
	vector<string> items;

	// Getting token for name.
	m_name = util.extractToken(line, pos, more);

	// Getting token for product.
	if (more)
	{
		m_product = util.extractToken(line, pos, more);
	}

	// Pushing item tokens into the vector.
	while (more)
	{
		items.push_back(util.extractToken(line, pos, more));
	}

	// Fetching the quantity of items.
	m_cntItem = items.size();
	// Allocating for Item.
	m_lstItem = new Item * [m_cntItem];

	// Assigning items (in Item).
	for (size_t i = 0; i < m_cntItem; i++)
	{
		m_lstItem[i] = new Item(items[i]);
	}

	// Updating width.
	if (m_widthField < util.getFieldWidth())
	{
		m_widthField = util.getFieldWidth();
	}
}

CustomerOrder::CustomerOrder(CustomerOrder& rhOrd)
{
	throw "----> ERROR: Cannot make copies.";
}

CustomerOrder::CustomerOrder(CustomerOrder&& rhOrd) noexcept
{
	m_name = rhOrd.m_name;
	m_product = rhOrd.m_product;
	m_cntItem = rhOrd.m_cntItem;
	m_lstItem = rhOrd.m_lstItem;

	// Moving object.
	rhOrd.m_name.clear();
	rhOrd.m_product.clear();
	rhOrd.m_cntItem = 0u;
	rhOrd.m_lstItem = nullptr;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rhOrd) noexcept
{
	// Checking for self-assignment.
	if (this != &rhOrd)
	{
		if (m_lstItem)
		{
			for (size_t i = 0u; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}

			delete[] m_lstItem;
		}
	}

	m_name = rhOrd.m_name;
	m_product = rhOrd.m_product;
	m_cntItem = rhOrd.m_cntItem;
	m_lstItem = rhOrd.m_lstItem;

	// Moving object.
	rhOrd.m_name.clear();
	rhOrd.m_product.clear();
	rhOrd.m_cntItem = 0u;
	rhOrd.m_lstItem = nullptr;

	return *this;
}

CustomerOrder::~CustomerOrder()
{
	for (size_t i = 0u; i < m_cntItem; i++)
	{
		delete m_lstItem[i];
	}

	delete[] m_lstItem;
	m_lstItem = nullptr;
}

bool CustomerOrder::isOrderFilled() const
{
	// Bool flags to escape the loop (one exit).
	bool isFilled = true;

	for (size_t i = 0; i < m_cntItem && isFilled; i++)
	{
		// Looking for a non-filled order.
		if (!m_lstItem[i]->s_isFilled)
		{
			isFilled = false;
		}
	}

	return isFilled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	// Bool flags to escape the loop (one exit).
	// As per documentation, assuming true.
	bool result = true;

	for (size_t i = 0u; i < m_cntItem; i++)
	{
		// Looking for an item with a name match.
		if (m_lstItem[i]->s_itemName == itemName && !m_lstItem[i]->s_isFilled)
		{
			// Checking if that item is filled.
			result = false;
		}
	}

	return result;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	// Bool flag to avoid printing more than once.
	bool isFilled = false;

	for (size_t i = 0u; i < m_cntItem && !isFilled; i++)
	{
		if (m_lstItem[i]->s_itemName == station.getItemName() && !m_lstItem[i]->s_isFilled)
		{
			// Verifying the existance of items.
			if (station.getQuantity() > 0)
			{
				// Subtracting 1 from the total.
				station.updateQuantity();
				// Getting serial number and updating the item status.
				m_lstItem[i]->s_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->s_isFilled = true;

				// Printing message.
				os << "    Filled " << m_name << ", " << m_product
					<< " [" << m_lstItem[i]->s_itemName << ']' << endl;

				isFilled = true;
			}
			// The inventory is empty.
			else
			{
				os << "    Unable to fill " << m_name << ", " << m_product
					<< " [" << m_lstItem[i]->s_itemName << ']' << endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << endl;

	for (size_t i = 0u; i < m_cntItem; i++)
	{
		// Fixing padding numbers with zeros (applying char).
		os << right << '[' << setw(6) << setfill('0') << m_lstItem[i]->s_serialNumber << "] ";
		os << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->s_itemName << " - ";

		if (m_lstItem[i]->s_isFilled)
		{
			os << "FILLED";
		}
		else
		{
			os << "TO BE FILLED";
		}

		os << endl;
	}
}