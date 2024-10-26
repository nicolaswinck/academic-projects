#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>

class Movie
{
	std::string m_title;
	size_t m_year;
	std::string m_description;

public:
	Movie();
	// Trimming utility.
	std::string trim(std::string token);
	const std::string& title() const;
	Movie(const std::string& strMovie);

	template <typename T>
	void fixSpelling(T& spellChecker)
	{
		spellChecker(m_title);
		spellChecker(m_description);
	}

	friend std::ostream& operator<<(std::ostream& ostr, const Movie& movie);
};

#endif