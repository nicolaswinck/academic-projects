#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"

using namespace std;

// Defining class variable.
char Utilities::m_delimiter = ' ';

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{
	// Setting start position and token to begin.
	size_t start_pos = next_pos;
	string token = "";

	// Updating next position (finding delimiter).
	next_pos = str.find(m_delimiter, start_pos);

	// Exception: delimiter is found in next position.
	if (start_pos == next_pos)
	{
		more = false;
		throw "   ERROR: Delimiter found.\n";
	}

	// The delimiter is found.
	if (next_pos != string::npos)
	{
		// Trimming a substring within the position's bounds.
		token = trim(str.substr(start_pos, next_pos - start_pos));

		// Updating width.
		if (token.length() > m_widthField)
		{
			m_widthField = token.length();
		}

		more = true;
	}
	// The delimiter is not found.
	else
	{
		// Trimming a substring from the position to the end.
		token = trim(str.substr(start_pos));

		// Updating width.
		if (token.length() > m_widthField)
		{
			m_widthField = token.length();
		}

		more = false;
	}

	// Incrementing next position.
	next_pos++;

	return token;
}

string Utilities::trim(string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}

void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
	return m_delimiter;
}