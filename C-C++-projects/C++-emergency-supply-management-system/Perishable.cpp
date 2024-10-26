#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iomanip>
#include <string.h>
#include "Perishable.h"
#include "Utils.h"

using namespace std;

// Creating empty Perishable item.
Perishable::Perishable() : Item()
{
	m_instructions = nullptr;
}

// Creating empty Perishable "other" item.
Perishable::Perishable(const Perishable& per) : Item(per)
{
	m_instructions = nullptr;
	m_expDate = per.m_expDate;
	// Deallocating memory.
	delete[] m_instructions;
	m_instructions = nullptr;
	// Copying the "other" instructions to this object.
	if (per.m_instructions != nullptr)
	{
		ut.alocpy(m_instructions, per.m_instructions);
	}
	else
	{
		m_instructions = nullptr;
	}
}

Perishable& Perishable::operator=(const Perishable& per)
{
	// Checking for self-assignment.
	if (this != &per)
	{
		// Calling the assignment operator for Item.
		Item::operator=(per);
		// Adding the expiration date.
		m_expDate = per.m_expDate;
		// Deallocating memory.
		delete[] m_instructions;
		m_instructions = nullptr;

		if (per.m_instructions != nullptr)
		{
			ut.alocpy(m_instructions, per.m_instructions);
		}
		else
		{
			m_instructions = nullptr;
		}
	}

	return *this;
}

Perishable::~Perishable()
{
	delete[] m_instructions;
	m_instructions = nullptr;
}

const Date& Perishable::expiry() const
{
	return m_expDate;
}

int Perishable::readSku(std::istream& istr)
{
	int input{};
	// Foolproof input for integer.
	cout << "SKU: ";
	// Changing the sku constraints.
	input = ut.getInt(10000, 39999);
	m_sku = input;

	return m_sku;
}

std::ofstream& Perishable::save(std::ofstream& ofstr) const
{
	// Checking for good state (empty).
	if (m_state == nullptr)
	{
		// Creating temporary date to unformat.
		Date tempDate = m_expDate;
		// Saving the Item details.
		Item::save(ofstr);

		// Separators.
		ofstr << '\t';

		if (m_instructions != nullptr && strlen(m_instructions) > 0)
		{
			// Adding instructions.
			ofstr << m_instructions;
		}

		ofstr << '\t';
		// Taking the format off the date.
		// e.g.: 2023/12/12 becomes 231212 when saved to the file.
		ofstr << tempDate.formatted(false);
	}

	return ofstr;
}

std::ifstream& Perishable::load(std::ifstream& ifstr)
{
	// Creating temporary instructions to pass the value to the attribute.
	char tempInstructions[4096];
	// Loading the Item details.
	Item::load(ifstr);

	if (m_instructions)
	{
		// Deallocating instructions.
		delete[] m_instructions;
		m_instructions = nullptr;
	}
	// Dynamically getting the instructions and assigning to the attribute.
	ifstr.getline(tempInstructions, sizeof(tempInstructions), '\t');
	ut.alocpy(m_instructions, tempInstructions);
	// Getting expiry date.
	ifstr >> m_expDate;
	// Fail state into file stream reading.
	if (ifstr.fail())
	{
		m_state = "Input file stream read (perishable) failed!";
	}

	return ifstr;
}

std::ostream& Perishable::display(std::ostream& ostr) const
{
	// Checking for bad state (not empty).
	if (m_state != nullptr)
	{
		ostr << m_state << endl;
	}
	// Good state (empty).
	else
	{
		if (linear())
		{
			// Displaying Item details.
			Item::display(ostr);
			// Adding detail to the instructions.
			if (m_instructions != nullptr && strlen(m_instructions) > 0)
			{
				ostr << '*';
			}
			else
			{
				ostr << ' ';
			}
			// Getting expiry date.
			ostr << m_expDate;
		}
		else
		{
			// Adding perishable tag.
			ostr << "Perishable ";
			// Displaying Item details.
			Item::display(ostr);

			ostr << "Expiry date: " << m_expDate << endl;

			if (m_instructions != nullptr && strlen(m_instructions) > 0)
			{
				ostr << "Handling Instructions: " << m_instructions << endl;
			}
		}
	}

	return ostr;
}

std::istream& Perishable::read(std::istream& istr)
{
	// Creating another temporary string to pass the instructions.
	char tempInstructions[4096];

	if (Item::read(istr).fail())
	{
		m_state = "Input file stream read failed!";
	}
	else
	{
		if (m_instructions)
		{
			delete[] m_instructions;
			m_instructions = nullptr;
		}

		cout << "Expiry date (YYMMDD): ";
		istr >> m_expDate;

		cout << "Handling Instructions, ENTER to skip: ";
		// Peeking for newline (so the user can skip adding instructions).
		if (istr.peek() != '\n')
		{
			// Getting instructions until <ENTER> key.
			istr.getline(tempInstructions, 4096, '\n');
			// Copying instructions.
			if (tempInstructions[0] != '\0')
			{
				ut.alocpy(m_instructions, tempInstructions);
			}
		}
		else
		{
			istr.ignore(10000, '\n');
		}

		if (istr.fail())
		{
			m_state = "Perishable console date entry failed!";
		}
	}

	return istr;
}