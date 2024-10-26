#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iomanip>

// Forward declaration to establish relationship.
class Reservation;

class Restaurant
{
	const Reservation** m_reservations;
	size_t m_numOfReservations;

public:
	Restaurant();
	Restaurant(const Reservation* reservations[], size_t cnt);
	// Copy constructor + copy assignment operator.
	Restaurant(const Restaurant& rhr);
	Restaurant& operator=(const Restaurant& rhr);
	// Move constructor + move assignment operator.
	Restaurant(Restaurant&& rhr) noexcept;
	Restaurant& operator=(Restaurant&& rhr) noexcept;
	~Restaurant();
	// Query for size.
	size_t size() const;

	// Insertion operator overload (friend operator).
	friend std::ostream& operator<<(std::ostream& os, const Restaurant& rest);
};

#endif