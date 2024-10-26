#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <iomanip>
#include "CarSystem.h"

using namespace std;

void CarInventory::resetInfo()
{
	m_type = nullptr;
	m_brand = nullptr;
	m_model = nullptr;
	m_year = 0;
	m_code = 0;
	m_price = 0.0;
}

// Constructor overload #1.
CarInventory::CarInventory()
{
	resetInfo();
}

CarInventory::~CarInventory()
{
	delete[] m_type;
	delete[] m_brand;
	delete[] m_model;
}

// Constructor overload #2.
CarInventory::CarInventory(const char* type, const char* brand, const char* model)
{
	// Reseting members.
	resetInfo();
	// Setting data with default values for arguments.
	setInfo(type, brand, model, 2022, 100, 1.0);
}

// Constructor overload #3.
CarInventory::CarInventory(const char* type, const char* brand,
	const char* model, int year, int code, double price)
{
	// Reseting members.
	resetInfo();
	// Setting data for all the arguments.
	setInfo(type, brand, model, year, code, price);
}

CarInventory& CarInventory::setInfo(const char* type, const char* brand,
	const char* model, int year, int code, double price)
{
	delete[] m_type;
	delete[] m_brand;
	delete[] m_model;

	resetInfo();

	if (!isValid())
	{
		// Dynamically assigning strings.
		m_type = new char[strlen(type) + 1];
		strcpy(m_type, type);

		m_brand = new char[strlen(brand) + 1];
		strcpy(m_brand, brand);

		m_model = new char[strlen(model) + 1];
		strcpy(m_model, model);

		// Assigning numerical members.
		m_year = year;
		m_code = code;
		m_price = price;
	}

	// Returning current object.
	return *this;
}

void CarInventory::printInfo() const
{
	cout << "| " << setw(11) << left << m_type;
	cout << "| " << setw(17) << m_brand;
	cout << "| " << setw(17) << m_model;
	cout << "| " << setw(5) << m_year;
	cout << "| " << setw(4) << right << m_code;
	cout << " | " << setw(9) << right << fixed << setprecision(2) << m_price;
	cout << " |" << endl;
}

bool CarInventory::isValid() const
{
	// Validating all the members information.
	bool result =
		m_type != nullptr &&
		m_brand != nullptr &&
		m_model != nullptr &&
		m_year >= 1990 &&
		(m_code > 99 && m_code < 1000) &&
		m_price > 0.0;

	return result;
}

bool CarInventory::isSimilarTo(const CarInventory& car) const
{
	bool result = false;

	// Checking for nullptrs.
	if (m_type == nullptr ||
		m_brand == nullptr ||
		m_model == nullptr)
	{
		result = false;
	}
	// Comparing members.
	else
	{
		if (!strcmp(car.m_type, m_type) &&
			!strcmp(car.m_brand, m_brand) &&
			!strcmp(car.m_model, m_model) &&
			car.m_year == m_year)
		{
			result = true;
		}
	}

	return result;
}

int find_similar(CarInventory car[], const int num_cars)
{
	int match = 0;

	for (int i = 0; i < num_cars; i++)
	{
		for (int j = i + 1; j < num_cars; j++)
		{
			if (car[i].isSimilarTo(car[j]))
			{
				match = i; // A match is found.
			}
		}
	}

	// Returning index.
	return match;
}