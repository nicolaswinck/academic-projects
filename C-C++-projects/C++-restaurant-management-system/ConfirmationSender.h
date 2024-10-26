#ifndef CONFIRMATIONSENDER_H
#define CONFIRMATIONSENDER_H

#include <iomanip>
#include "Reservation.h"

class ConfirmationSender
{
	const Reservation** m_reservations;
	size_t m_numOfReservations;

public:
	ConfirmationSender();
	// Copy constructor + copy assignment operator.
	ConfirmationSender(const ConfirmationSender& rhcs);
	ConfirmationSender& operator=(const ConfirmationSender& rhcs);
	// Move constructor + move assignment operator.
	ConfirmationSender(ConfirmationSender&& rhcs) noexcept;
	ConfirmationSender& operator=(ConfirmationSender&& rhcs) noexcept;
	~ConfirmationSender();
	// Operators to manage reservations.
	ConfirmationSender& operator+=(const Reservation& res);
	ConfirmationSender& operator-=(const Reservation& res);

	// Insertion operator overload (friend operator).
	friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& conf);
};

#endif