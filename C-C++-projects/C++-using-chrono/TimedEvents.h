#ifndef TIMEDEVENTS_H
#define TIMEDEVENTS_H

#include <chrono>

// Declaring the array of Event objects.
struct Event
{
	char* name;
	char* timeUnits;
	std::chrono::steady_clock::duration duration;
};

class TimedEvents
{
	// Statically allocating 10 objects (constant).
	static const int MAX_EVENTS = 10;
	int m_numRecords;
	std::chrono::steady_clock::time_point m_startTime;
	std::chrono::steady_clock::time_point m_endTime;
	// The array (initialized).
	Event event[MAX_EVENTS];

public:

	TimedEvents();
	// Rule of three.
	~TimedEvents();
	TimedEvents(const TimedEvents& rhEv);
	TimedEvents& operator=(const TimedEvents& rhEv);
	void startClock();
	void stopClock();
	void addEvent(const char* eventName);

	friend std::ostream& operator<<(std::ostream& ostr, const TimedEvents& ev);
};

#endif