#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Toy.h"

using namespace std;

// Function to get rid of leading and trailling whitespaces.
string Toy::trim(string str)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = str.find_first_not_of(space);
	size_t end = str.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return str.substr(start, (end - start) + 1);
}

Toy::Toy()
{
	m_orderId = 0;
	m_name = {};
	m_numItems = 0;
	m_price = 0.0;
	m_hst = 0.0;
}

Toy::Toy(const Toy& rht)
{
	// Assigning (copying) the righthand object to this.
	m_orderId = rht.m_orderId;
	m_name = rht.m_name;
	m_numItems = rht.m_numItems;
	m_price = rht.m_price;
	m_hst = rht.m_hst;
}

void Toy::update(int numItems)
{
	m_numItems = numItems;
}

Toy::Toy(const string& toy)
{
	// Declaring temporary strings to pass the data to the attributes.
	string tempToy = toy;
	string tempId;
	string tempName;
	string tempNumItems;
	string tempPrice;
	// Defining the separator (colon).
	char sep = ':';
	// Assigning the index where the separator is.
	size_t idx_sep = tempToy.find(sep);
	// Getting the ID and trimming.
	tempId = tempToy.substr(0, idx_sep);
	tempId = trim(tempId);
	// Redefining the whole string.
	tempToy = tempToy.substr(idx_sep + 1, tempToy.length());
	idx_sep = tempToy.find(sep);
	// Getting the name and trimming.
	tempName = tempToy.substr(0, idx_sep);
	tempName = trim(tempName);
	// Redefining the whole string.
	tempToy = tempToy.substr(idx_sep + 1, tempToy.length());
	idx_sep = tempToy.find(sep);
	// Getting the number of items and trimming.
	tempNumItems = tempToy.substr(0, idx_sep);
	tempNumItems = trim(tempNumItems);
	// Redefining the whole string.
	tempToy = tempToy.substr(idx_sep + 1, tempToy.length());
	idx_sep = tempToy.find(sep);
	// Getting the price and trimming.
	tempPrice = tempToy.substr(0, idx_sep);
	tempPrice = trim(tempPrice);

	// Converting the temp strings to the attributes' types and assigning.
	m_orderId = stoi(tempId);
	m_name = tempName;
	m_numItems = stoi(tempNumItems);
	m_price = stod(tempPrice);
	// Standard HST = 13% as per documentation.
	m_hst = 0.13;
}

ostream& operator<<(ostream& ostr, const Toy& toy)
{
	// Calculating the subtotal.
	double subtotal = toy.m_price * toy.m_numItems;

	// Printing out as per documentation's step-by-step.
	ostr << "Toy";
	ostr << setw(8) << toy.m_orderId << ':';
	ostr << setw(18) << right << toy.m_name;
	ostr << setw(3) << toy.m_numItems;
	ostr << " items";
	ostr << setw(8) << toy.m_price;
	ostr << "/item  subtotal:";
	ostr << setw(7) << fixed << setprecision(2) << subtotal;
	ostr << " tax:";
	ostr << setw(6) << subtotal * toy.m_hst;
	ostr << " total:";
	ostr << setw(7) << subtotal + (subtotal * toy.m_hst) << endl;

	return ostr;
}