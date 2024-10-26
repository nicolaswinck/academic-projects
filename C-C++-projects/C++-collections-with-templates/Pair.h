#ifndef PAIR_H
#define PAIR_H

#include <cstring>
#include <iostream>

class Pair
{
	std::string m_key;
	std::string m_value;
public:
	const std::string& getKey() { return m_key; }
	const std::string& getValue() { return m_value; }
	Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value } {};

	// Default no-argument constructor.
	Pair();
	// Copy constructor.
	Pair(const Pair& rhp);
	// Copy assignment operator.
	Pair& operator=(const Pair& rhp);
	// Friend insertion operator.
	friend std::ostream& operator<<(std::ostream& ostr, const Pair& rhp);
	// Friend comparison operator.
	friend bool operator==(const Pair& lhp, const Pair& rhp);
};

#endif