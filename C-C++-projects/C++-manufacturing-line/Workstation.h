#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation{ nullptr };

public:
	Workstation(const std::string& line);
	void fill(std::ostream& os);
	bool attemptToMoveOrder();
	void setNextStation(Workstation* station = nullptr);
	Workstation* getNextStation() const;
	void display(std::ostream& os) const;
	Workstation& operator+=(CustomerOrder&& newOrder);
	// Copy constructor (deleted).
	Workstation(const Workstation& rhWork) = delete;
	// Copy assignment operator (deleted).
	Workstation& operator=(const Workstation& rhWork) = delete;
	// Move constructor and assignment operators (deleted).
	Workstation(const Workstation&& rhWork) = delete;
	Workstation& operator=(Workstation&& rhWork) = delete;
};

#endif