#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Movie.h"

using namespace std;

Movie::Movie() : m_title(), m_year(0u), m_description() {}

std::string Movie::trim(std::string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}

const std::string& Movie::title() const
{
	return m_title;
}

Movie::Movie(const std::string& strMovie)
{
	// Temporary attribute holders.
	string tempTitle;
	string tempYear;
	string tempDescr;
	// Separator
	char sep = ',';
	// Index containing the separator.
	size_t idxSep = strMovie.find(sep);
	// Fixing size for the number of separators expected.
	const size_t SEP_NUM = 2;
	// Array to store the indexes with the separators.
	size_t idxArr[SEP_NUM] = { 0 };

	// Getting the indexes with the separators.
	for (size_t counter = 0; idxSep != strMovie.length()
		&& counter < SEP_NUM; counter++)
	{
		idxArr[counter] = idxSep;
		idxSep = strMovie.find(sep, idxSep + 1);
	}

	// Getting substrings with separator indexes and trimming spaces.
	tempTitle = trim(strMovie.substr(0, idxArr[0]));
	tempYear = trim(strMovie.substr(idxArr[0] + 1, (idxArr[1] - idxArr[0]) - 1));
	// Considering the description as the last attribute.
	tempDescr = trim(strMovie.substr(idxArr[1] + 1, strMovie.length() - idxArr[1]));

	// Assigning temporary strings to the attributes.
	m_title = tempTitle;
	m_year = stoi(tempYear);
	m_description = tempDescr;
}

std::ostream& operator<<(std::ostream& ostr, const Movie& movie)
{
	ostr << setw(40) << movie.m_title << " | ";
	ostr << setw(4) << movie.m_year << " | ";
	ostr << movie.m_description << endl;

	return ostr;
}