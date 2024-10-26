#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

class Utilities
{
	// Starting with default unsigned value.
	size_t m_widthField{ 1u };

public:
	// Declaring class variable.
	static char m_delimiter;

	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	// Custom trimming utility (the same one I used on previous workshops).
	std::string trim(std::string token);
	// Class functions.
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
};

#endif