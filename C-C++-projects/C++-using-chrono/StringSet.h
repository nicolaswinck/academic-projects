#ifndef STRINGSET_H
#define STRINGSET_H

class StringSet
{
	// Dynamically allocated array of string objects.
	std::string* m_elements;
	// Number of strings (type to match the last operator's argument).
	size_t m_stringsNum;

public:

	StringSet();
	// Rule of three.
	~StringSet();
	StringSet(const StringSet& rhStr);
	StringSet& operator=(const StringSet& rhStr);
	// Move constructor and move assignment operator.
	StringSet(StringSet&& rhStr) noexcept;
	StringSet& operator=(StringSet&& rhStr) noexcept;
	StringSet(const char* fileName);
	size_t size() const;
	std::string operator[](size_t num) const;
};

#endif