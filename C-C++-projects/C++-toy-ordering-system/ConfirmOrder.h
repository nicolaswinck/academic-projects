#ifndef CONFIRMORDER_H
#define CONFIRMORDER_H

#include <cstring>
#include <iostream>
#include "Toy.h"

class ConfirmOrder
{
	// The array and the size.
	const Toy** m_toys;
	size_t m_numOfToys;

public:
	// Default constructor.
	ConfirmOrder();
	// Destructor.
	~ConfirmOrder();
	// Copy constructor.
	ConfirmOrder(const ConfirmOrder& rho);
	// Copy assignment operator.
	ConfirmOrder& operator=(const ConfirmOrder& rho);
	// Move constructor.
	ConfirmOrder(ConfirmOrder&& rho) noexcept;
	// Move assignment operator.
	ConfirmOrder& operator=(ConfirmOrder&& rho) noexcept;
	// Add and remove operators.
	ConfirmOrder& operator+=(const Toy& toy);
	ConfirmOrder& operator-=(const Toy& toy);
	// Insertion operator (overload).
	friend std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& confOrd);
};

#endif