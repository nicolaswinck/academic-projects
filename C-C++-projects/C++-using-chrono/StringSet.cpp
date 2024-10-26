#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include "StringSet.h"

using namespace std;

StringSet::StringSet()
{
	m_elements = nullptr;
	m_stringsNum = 0;
}

StringSet::StringSet(const char* fileName)
{
	m_elements = nullptr;
	m_stringsNum = 0;

	// Creating ifstream object for the file and temporary string.
	ifstream inputFile(fileName);
	string holdString;

	if (inputFile.is_open())
	{
		// Assigning the data to the temp string.
		while (getline(inputFile, holdString, ' '))
		{
			// Counting the lines in each file.
			m_stringsNum++;
		}

		// Allocating.
		m_elements = new string[m_stringsNum];

		// Clearing and pointing to the beginning of the file to start over.
		inputFile.clear();
		inputFile.seekg(0);

		// Assigning the strings from the temp string to the attribute.
		unsigned int idx = 0;
		while (getline(inputFile, holdString, ' ') && idx < m_stringsNum)
		{
			m_elements[idx] = holdString;
			idx++;
		}
	}
	// Handling error reading the file.
	else
	{
		cerr << "Unable to read file " << fileName << endl;
	}

	// Closing the file.
	inputFile.close();
}

StringSet::~StringSet()
{
	delete[] m_elements;
	m_elements = nullptr;
}

StringSet::StringSet(const StringSet& rhStr)
{
	// Copying the right-hand object to this.
	m_stringsNum = rhStr.m_stringsNum;
	// Allocating.
	m_elements = new string[m_stringsNum];

	// Copying each element.
	for (size_t i = 0; i < m_stringsNum; i++)
	{
		m_elements[i] = rhStr.m_elements[i];
	}
}

StringSet& StringSet::operator=(const StringSet& rhStr)
{
	// Checking for self-assignment.
	if (this != &rhStr)
	{
		m_stringsNum = rhStr.m_stringsNum;

		delete[] m_elements;
		m_elements = new string[m_stringsNum];

		for (size_t i = 0; i < m_stringsNum; i++)
		{
			m_elements[i] = rhStr.m_elements[i];
		}
	}

	return *this;
}

StringSet::StringSet(StringSet&& rhStr) noexcept
{
	// Copying from the right-hand object to this.
	m_stringsNum = rhStr.m_stringsNum;
	m_elements = rhStr.m_elements;
	// Deallocating the other object (moving data).
	rhStr.m_elements = nullptr;
	rhStr.m_stringsNum = 0;
}

StringSet& StringSet::operator=(StringSet&& rhStr) noexcept
{
	// Checking for self-assignment.
	if (this != &rhStr)
	{
		// Deallocating this and copying.
		delete[] m_elements;
		m_elements = rhStr.m_elements;

		m_stringsNum = rhStr.m_stringsNum;
		// Deallocating the other object (moving data).
		rhStr.m_elements = nullptr;
		rhStr.m_stringsNum = 0;
	}

	return *this;
}

size_t StringSet::size() const
{
	return m_stringsNum;
}

string StringSet::operator[](size_t num) const
{
	// Flag with the string that will be displayed.
	string result;

	// Case for valid index.
	if (num < m_stringsNum)
	{
		result = m_elements[num];
	}
	// Case for invalid index (returning empty string).
	else
	{
		result = "";
	}

	return result;
}