#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "Train.h"
using namespace std;

void Train::initialize()
{
	trainName = nullptr;
	passengerNum = -1;
	departTime = -1;
}

bool Train::validTime(int value) const
{
	bool result = false;

	// Adding condition: valid time must display hour + minutes up to 59.
	if (value > MIN_TIME && value < MAX_TIME && value % 100 < 60)
	{
		result = true;
	}

	return result;
}

bool Train::validNoOfPassengers(int value) const
{
	bool result = false;

	if (value > 0 && value <= MAX_NO_OF_PASSENGERS)
	{
		result = true;
	}

	return result;
}

bool Train::load(int& unboarded)
{
	bool result = false;
	int boarded, newTotal;

	cout << "Enter number of passengers boarding:" << endl << "> ";
	cin >> boarded;

	newTotal = passengerNum += boarded;

	if (newTotal > MAX_NO_OF_PASSENGERS)
	{
		unboarded = newTotal - MAX_NO_OF_PASSENGERS;
	}
	else
	{
		result = true;
	}

	return result;
}

bool Train::updateDepartureTime()
{
	bool result = false;
	int newDepartTime;

	cout << "Enter new departure time:" << endl << "> ";
	cin >> newDepartTime;

	if (validTime(newDepartTime))
	{
		departTime = newDepartTime;
		result = true;
	}
	else
	{
		departTime = -1;
	}

	return result;
}

void Train::set(const char* name)
{
	delete[] trainName;

	// Dynamically allocating string.
	if (name != nullptr && strlen(name))
	{
		trainName = new char[strlen(name) + 1];
		strcpy(trainName, name);
	}
}

void Train::set(int noOfPassengers, int departure)
{
	// Assigning valid values and marking invalid ones.
	if (validNoOfPassengers(noOfPassengers))
	{
		passengerNum = noOfPassengers;
	}
	else
	{
		passengerNum = -1;
	}

	if (validTime(departure))
	{
		departTime = departure;
	}
	else
	{
		departTime = -1;
	}
}

void Train::set(const char* name, int noOfPassengers, int departure)
{
	// Validating the three attributes.
	if (name != nullptr && validNoOfPassengers(noOfPassengers) && validTime(departure))
	{
		set(name);
		passengerNum = noOfPassengers;
		departTime = departure;
	}
	// Storing name if the passenger number or the departure is not valid.
	else if (!validNoOfPassengers(noOfPassengers) || !validTime(departure))
	{
		set(name);
	}
}

void Train::finalize()
{
	// Deleting memory and finalizing object.
	delete[] trainName;
}

bool Train::isInvalid() const
{
	bool result = false;

	if (departTime < 0 || passengerNum < 0 || trainName == nullptr)
	{
		result = true;
	}

	return result;
}

int Train::noOfPassengers() const
{
	return passengerNum;
}

const char* Train::getName() const
{
	return trainName;
}

int Train::getDepartureTime() const
{
	return departTime;
}

void Train::display() const
{
	if (!isInvalid())
	{
		cout << "NAME OF THE TRAIN:    " << getName() << endl;
		cout << "NUMBER OF PASSENGERS: " << noOfPassengers() << endl;
		cout << "DEPARTURE TIME:       " << getDepartureTime() << endl;
	}
	else
	{
		cout << "Train in an invalid State!" << endl;
	}
}

bool Train::transfer(const Train& train)
{
	bool result = false;
	int unboarded;
	char* temp1;

	if (validNoOfPassengers(train.passengerNum) && validNoOfPassengers(passengerNum))
	{
		// Dynamically creating temp array to store the new train name.
		temp1 = new char[strlen(trainName) + strlen(", ") + strlen(train.trainName) + 1];
		strcpy(temp1, trainName);
		// Adding the separator.
		strcat(temp1, ", ");
		// Concatenating the other name.
		strcat(temp1, train.trainName);
		// Setting the new name.
		set(temp1);

		passengerNum += train.passengerNum;

		if (passengerNum <= MAX_NO_OF_PASSENGERS)
		{
			result = true;
		}
		else
		{
			// Calculating unboarded passengers.
			unboarded = passengerNum - MAX_NO_OF_PASSENGERS;
			passengerNum -= unboarded;

			// Printing result.
			cout << "Train is full; " << unboarded << " passengers of "
				<< train.trainName << " could not be boarded!" << endl;

			result = true;
		}

		// Deallocating memory to avoid leaks.
		delete[] temp1;
	}

	return result;
}