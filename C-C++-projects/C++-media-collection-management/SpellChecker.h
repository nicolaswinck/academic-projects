#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <iostream>
#include <string>

// Fixing array size.
const size_t SIZE = 6;

class SpellChecker
{
	std::string m_badWords[SIZE] = {};
	std::string m_goodWords[SIZE] = {};
	size_t m_replacemCount[SIZE] = {};

public:
	SpellChecker(const char* filename);
	void operator()(std::string& text);
	void showStatistics(std::ostream& out) const;
};

#endif