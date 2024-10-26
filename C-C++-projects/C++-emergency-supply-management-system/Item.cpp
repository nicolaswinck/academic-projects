#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include "Utils.h"
#include "Item.h"

using namespace std;

bool Item::linear() const
{
	return m_linear;
}

Item::Item()
{
	m_price = 0.0;
	m_qty = 0;
	m_qtyNeeded = 0;
	m_description = nullptr;
	m_linear = false;
	m_state = nullptr;
	m_sku = 0;
}

Item::Item(const Item& it)
{
	// Copying all attributes.
	m_price = it.m_price;
	m_qty = it.m_qty;
	m_qtyNeeded = it.m_qtyNeeded;
	m_linear = it.m_linear;
	m_state = it.m_state;
	m_sku = it.m_sku;

	if (it.m_description != nullptr)
	{
		// Dynamically allocating description attribute.
		ut.alocpy(m_description, it.m_description);
	}
	else
	{
		// Deallocating.
		m_description = nullptr;
	}
}

Item& Item::operator=(const Item& it)
{
	// Checking for self-assignment.
	if (this != &it)
	{
		m_price = it.m_price;
		m_qty = it.m_qty;
		m_qtyNeeded = it.m_qtyNeeded;
		m_linear = it.m_linear;
		m_state = it.m_state;
		m_sku = it.m_sku;

		delete[] m_description;
		m_description = nullptr;

		if (it.m_description != nullptr)
		{
			ut.alocpy(m_description, it.m_description);
		}
		else
		{
			m_description = nullptr;
		}
	}

	return *this;
}

Item::~Item()
{
	delete[] m_description;
	m_description = nullptr;
}

int Item::qtyNeeded() const
{
	return m_qtyNeeded;
}

int Item::qty() const
{
	return m_qty;
}

Item::operator double() const
{
	return m_price;
}

Item::operator bool() const
{
	// Object in a good state (empty), with no meaningful data.
	return m_state == nullptr && (m_description != nullptr || m_sku != 0);
}

int Item::operator-=(int rhQty)
{
	// Reducing left operand by the right operand.
	m_qty -= rhQty;

	return m_qty;
}

int Item::operator+=(int rhQty)
{
	// Increasing the left operand by the right operand.
	m_qty += rhQty;

	return m_qty;
}

void Item::linear(bool linear)
{
	m_linear = linear;
}

void Item::clear()
{
	m_state = nullptr;
}

bool Item::operator==(int rhSku) const
{
	// True if the attribute and the right object are equal.
	return m_sku == rhSku;
}

bool Item::operator==(const char* rhDesc) const
{
	bool result = false;
	// Using substring to accurately match an item description.
	const char* found = strstr(m_description, rhDesc);

	if (m_description != nullptr && rhDesc != nullptr)
	{
		// A match is found.
		if (found != nullptr)
		{
			result = true;
		}
	}

	return result;
}

std::ofstream& Item::save(std::ofstream& ofstr) const
{
	// State is good (empty = ready).
	if (m_state == nullptr)
	{
		// ofstr object with attributes separated by <TAB> character.
		ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t';
		ofstr << m_qtyNeeded << '\t';
		// Setting two decimal points.
		ofstr << fixed << setprecision(2) << m_price;
	}

	return ofstr;
}

std::ifstream& Item::load(std::ifstream& ifstr)
{
	// Creating temporary string to store the description.
	char tempDescr[4096];

	if (m_description)
	{
		// Deallocating description.
		delete[] m_description;
		m_description = nullptr;
	}
	// Getting sku and ignoring \t character.
	ifstr >> m_sku;
	ifstr.ignore();
	// Getting the description and storing into the temp string.
	ifstr.getline(tempDescr, sizeof(tempDescr), '\t');
	ut.alocpy(m_description, tempDescr);
	// Getting the other attributes and discarding separator \t.
	ifstr >> m_qty >> m_qtyNeeded >> m_price;
	ifstr.ignore();
	// ifstr in bad state.
	if (ifstr.fail())
	{
		m_state = "Input file stream read failed!";
	}

	return ifstr;
}

std::ostream& Item::display(std::ostream& ostr) const
{
	// Calculating needed purchase fund.
	double neededPurchFund = (m_qtyNeeded - m_qty) * m_price;
	// Bad state.
	if (m_state != nullptr)
	{
		ostr << m_state;
	}
	// Good state.
	else
	{
		// Linear format.
		if (linear())
		{
			// Aligning to the left with 5 chars.
			ostr << left << setw(5) << m_sku << " | ";
			// Casting string to fetch substring and limit to 35 chars.
			ostr << left << setw(35) << setfill(' ');
			ostr << string(m_description).substr(0, 35) << " | ";
			// Aligning to the right with 4 chars.
			ostr << right << setw(4) << setfill(' ') << m_qty << " | ";
			ostr << right << setw(4) << setfill(' ') << m_qtyNeeded << " | ";
			// Setting two decimal points.
			ostr << fixed << setprecision(2) << setw(7) << setfill(' ') << m_price << " |";
		}
		// Desctiptive format.
		else
		{
			ostr << "AMA Item:" << endl;
			ostr << m_sku << ": " << m_description << endl;
			ostr << "Quantity Needed: " << m_qtyNeeded << endl;
			ostr << "Quantity Available: " << m_qty << endl;
			// Setting two decimal points.
			ostr.setf(ios::fixed);
			ostr.precision(2);
			ostr << "Unit Price: $" << m_price << endl;
			ostr << "Needed Purchase Fund: $" << neededPurchFund << endl;
		}
	}

	return ostr;
}

int Item::readSku(std::istream& istr)
{
	int input{};
	// Foolproof input for integer.
	cout << "SKU: ";
	input = ut.getInt(40000, 99999);
	m_sku = input;

	return m_sku;
}

std::istream& Item::read(std::istream& istr)
{
	// Temporary string to store the item description.
	char tempDescr[4096];
	// Temporary variables to store the input results.
	int tempQtyNeed{};
	int tempQty{};
	double tempPrice{};

	if (m_description)
	{
		// Deallocating.
		delete[] m_description;
		m_description = nullptr;
	}
	clear();

	cout << "AMA Item:" << endl;
	cout << "SKU: " << m_sku << endl;
	// Getting description and copying to attribute.
	cout << "Description: ";
	istr.getline(tempDescr, 4096);
	if (istr)
	{
		ut.alocpy(m_description, tempDescr);
	}
	// Getting the other values.
	cout << "Quantity Needed: ";
	tempQtyNeed = ut.getInt(1, 9999);
	m_qtyNeeded = tempQtyNeed;

	cout << "Quantity On Hand: ";
	tempQty = ut.getInt(0, m_qtyNeeded);
	m_qty = tempQty;

	cout << "Unit Price: $";
	tempPrice = ut.getDouble(0.0, 9999.0);
	m_price = tempPrice;
	// istr in a bad state.
	if (istr.fail())
	{
		m_state = "Console entry failed!";
	}

	return istr;
}