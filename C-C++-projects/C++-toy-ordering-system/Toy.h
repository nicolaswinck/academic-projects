#ifndef TOY_H
#define TOY_H

#include <cstring>
#include <iostream>

class Toy
{
	unsigned int m_orderId;
	std::string m_name;
	int m_numItems;
	double m_price;
	double m_hst;
	// Private method.
	std::string trim(std::string str);

public:
	// Default constructor.
	Toy();
	// Copy constructor.
	Toy(const Toy& rht);
	void update(int numItems);
	Toy(const std::string& toy);
	// Insertion overload.
	friend std::ostream& operator<<(std::ostream& ostr, const Toy& toy);
};

#endif