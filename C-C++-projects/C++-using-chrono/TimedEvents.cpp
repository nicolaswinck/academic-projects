#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <cstring>
#include "TimedEvents.h"

using namespace std;

TimedEvents::TimedEvents()
{
	m_numRecords = 0;

	// Initializing each object from the array.
	for (int i = 0; i < MAX_EVENTS; i++)
	{
		event[i].name = nullptr;
		event[i].timeUnits = nullptr;
	}
}

TimedEvents::~TimedEvents()
{
	// Destroying each object from the array.
	for (int i = 0; i < MAX_EVENTS; i++)
	{
		delete[] event[i].name;
		delete[] event[i].timeUnits;
	}
}

void seneca::TimedEvents::startClock()
{
	// Starting the timer now().
	m_startTime = std::chrono::steady_clock::now();
}

void TimedEvents::stopClock()
{
	// Stopping the timer now().
	m_endTime = std::chrono::steady_clock::now();
}

TimedEvents::TimedEvents(const TimedEvents& rhEv)
{
	// Copying the right-hand objects to this object.
	m_numRecords = rhEv.m_numRecords;
	m_startTime = rhEv.m_startTime;
	m_endTime = rhEv.m_endTime;

	// Copying all the events.
	for (int i = 0; i < MAX_EVENTS; i++)
	{
		event[i] = rhEv.event[i];
	}
}

void TimedEvents::addEvent(const char* eventName)
{
	// Checking for the array boundaries before creating new Event.
	if (m_numRecords < MAX_EVENTS)
	{
		// Storing the new name for the Event.
		event[m_numRecords].name = new char[strlen(eventName) + 1];
		strcpy(event[m_numRecords].name, eventName);
		// Storing the units of time.
		event[m_numRecords].timeUnits = new char[strlen("nanoseconds") + 1];
		strcpy(event[m_numRecords].timeUnits, "nanoseconds");
		// Calculating the duration (delta).
		event[m_numRecords].duration =
			std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);

		// Updating the number of events stored.
		m_numRecords++;
	}
}

TimedEvents& TimedEvents::operator=(const TimedEvents& rhEv)
{
	// Checking for self-assignment.
	if (this != &rhEv)
	{
		// Copying the right-hand objects to this object.
		m_numRecords = rhEv.m_numRecords;
		m_startTime = rhEv.m_startTime;
		m_endTime = rhEv.m_endTime;

		// Copying all the events.
		for (int i = 0; i < MAX_EVENTS; i++)
		{
			event[i] = rhEv.event[i];
		}
	}

	return *this;
}

ostream& operator<<(ostream& ostr, const TimedEvents& ev)
{
	// Printing out the header as shown in the output example.
	ostr << "--------------------------" << endl;
	ostr << "Execution Times:" << endl;
	ostr << "--------------------------" << endl;

	// Printing the records accordingly.
	for (int i = 0; i < ev.m_numRecords; i++)
	{
		// Field of size 21, aligned to the left, for the name of the Event.
		ostr << setw(21) << left << ev.event[i].name;
		// Field of size 13, aligned to the right, for the duration of the Event.
		ostr << setw(13) << right << ev.event[i].duration.count();
		ostr << " " << ev.event[i].timeUnits << endl;
	}

	ostr << "--------------------------" << endl;

	return ostr;
}