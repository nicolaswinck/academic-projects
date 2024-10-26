#ifndef STATION_H
#define STATION_H

#include <iostream>

class Station
{
	// Initializing instance variables.
	int m_id{ 0 };
	std::string m_itemName{ "" };
	std::string m_descr{ "" };
	size_t m_serial{ 0u };
	size_t m_qty{ 0u };

public:
	// Class variables.
	static size_t m_widthField;
	static size_t id_generator;

	Station(const std::string& line);
	const std::string& getItemName() const;
	size_t getNextSerialNumber();
	size_t getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif 