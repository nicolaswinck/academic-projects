#ifndef BOOK_H
#define BOOK_H

#include <iostream>

class Book
{
	std::string m_autor;
	std::string m_title;
	std::string m_country;
	size_t m_year;
	double m_price;
	std::string m_description;

public:
	Book();
	// Trimming utility.
	std::string trim(std::string token);
	const std::string& title() const;
	const std::string& country() const;
	const size_t& year() const;
	double& price();
	Book(const std::string& strBook);

	template <typename T>
	void fixSpelling(T& spellChecker)
	{
		spellChecker(m_description);
	}

	friend std::ostream& operator<<(std::ostream& ostr, const Book& book);
};

#endif