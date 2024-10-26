#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"

using namespace std;

Book::Book() : m_autor(), m_title(), m_country(), m_year(0u),
m_price(0.0), m_description() {}

std::string Book::trim(std::string token)
{
	// Defining the character to be trimmed.
	char space = ' ';
	// Getting the first and the last non-whitespace characters on string.
	size_t start = token.find_first_not_of(space);
	size_t end = token.find_last_not_of(space);

	// Returning the string without the spaces at the edges.
	return token.substr(start, (end - start) + 1);
}

const string& Book::title() const
{
	return m_title;
}

const string& Book::country() const
{
	return m_country;
}

const size_t& Book::year() const
{
	return m_year;
}

double& Book::price()
{
	return m_price;
}

Book::Book(const string& strBook)
{
	// Temporary attribute holders.
	string tempAuthor;
	string tempTitle;
	string tempCountry;
	string tempPrice;
	string tempYear;
	string tempDescr;
	// Separator
	char sep = ',';
	// Index containing the separator.
	size_t idxSep = strBook.find(sep);
	// Fixing size for the number of separators expected.
	const size_t SEP_NUM = 5;
	// Array to store the indexes with the separators.
	size_t idxArr[SEP_NUM] = { 0 };

	// Getting the indexes with the separators.
	for (size_t counter = 0; idxSep != strBook.length()
		&& counter < SEP_NUM; counter++)
	{
		idxArr[counter] = idxSep;
		idxSep = strBook.find(sep, idxSep + 1);
	}

	// Getting substrings with separator indexes and trimming spaces.
	tempAuthor = trim(strBook.substr(0, idxArr[0]));
	tempTitle = trim(strBook.substr(idxArr[0] + 1, (idxArr[1] - idxArr[0]) - 1));
	tempCountry = trim(strBook.substr(idxArr[1] + 1, (idxArr[2] - idxArr[1]) - 1));
	tempPrice = trim(strBook.substr(idxArr[2] + 1, (idxArr[3] - idxArr[2]) - 1));
	tempYear = trim(strBook.substr(idxArr[3] + 1, (idxArr[4] - idxArr[3]) - 1));
	// Considering the description as the last attribute.
	tempDescr = trim(strBook.substr(idxArr[4] + 1, strBook.length() - idxArr[4]));

	// Assigning temporary strings to the attributes.
	m_autor = tempAuthor;
	m_title = tempTitle;
	m_country = tempCountry;
	m_price = stod(tempPrice);
	m_year = stoi(tempYear);
	m_description = tempDescr;
}

ostream& operator<<(ostream& ostr, const Book& book)
{
	ostr << setw(20) << book.m_autor << " | ";
	ostr << setw(22) << book.m_title << " | ";
	ostr << setw(5) << book.m_country << " | ";
	ostr << setw(4) << book.m_year << " | ";
	// Adjusting precision to two decimal places.
	ostr << setw(6) << fixed << setprecision(2) << book.m_price << " | ";
	ostr << book.m_description << endl;

	return ostr;
}