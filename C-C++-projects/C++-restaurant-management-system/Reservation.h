#ifndef RESERVATION_H
#define RESERVATION_H

#include <iomanip>

class Reservation
{
	std::string m_id;
	std::string m_name;
	std::string m_email;
	int m_numOfPeople;
	int m_day;
	int m_hour;

public:
	Reservation();
	Reservation(const std::string& res);
	void update(int day, int time);
	// Function I made to help formatting the reservation.
	std::string trim(std::string str);
	// Friend helper insertion operator.
	friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
};

#endif