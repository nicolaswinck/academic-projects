#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Flight.h"

using namespace std;

void Flight::emptyPlane() {
    m_passengers = 0;
    m_fuel = 0;
    strcpy(m_title, "EmptyPlane");
}

// New Flight
Flight::Flight() {
    emptyPlane();
}
Flight::Flight(int passengers, double fuel, const char* title) {
    emptyPlane();
    if (passengers > 0 && passengers <= Boen747Capacity && fuel >= 0 &&
        fuel <= FuelTankCapacity) {
        m_passengers = passengers;
        m_fuel = fuel;
        strcpy(m_title, title);
    }
}
std::ostream& Flight::display() const {

    if (*this) {
        cout << " Flight  |  Ready to Depart";
        cout << " ";
        cout.width(10);
        cout << std::string(*this);
        cout << " | ";
        cout << "Pass: ";
        cout.width(10);
        cout << int(*this);
        cout << " | ";
        cout.width(12);
        cout.precision(2);
        cout.setf(ios::right);
        cout.setf(ios::fixed);
        cout << double(*this);
        cout.unsetf(ios::right);
        cout << " Liters";
    }
    else if (~*this) {
        cout << " Flight  |  Empty Plane    ";
    }
    else {
        cout << " Flight  |  Low Fuel       ";
        cout << " ";
        cout.width(10);
        cout << (const char*)(*this);
        cout << " | ";
        cout << "Pass: ";
        cout.width(10);
        cout << int(*this);
        cout << " | ";
        cout.width(12);
        cout.precision(2);
        cout.setf(ios::right);
        cout.setf(ios::fixed);
        cout << double(*this);
        cout.unsetf(ios::right);
        cout << " Liters";
    }
    return cout;
}

// Type conversion operators.

Flight::operator bool() const
{
    bool result = false;
    double minFuel = 0;

    // Checking for at least one passenger aboard.
    if (m_passengers > 0)
    {
        // Setting the minimum fuel per passenger on this flight.
        minFuel = m_fuel / m_passengers;
        // Verifying fuel.
        if (minFuel >= 600)
        {
            result = true;
        }
    }

    return result;
}

Flight::operator int() const
{
    return m_passengers;
}

Flight::operator double() const
{
    return m_fuel;
}

Flight::operator const char* () const
{
    return m_title;
}

// Unary operator.

bool Flight::operator~() const
{
    return m_passengers == 0;
}

// Binary operators.

Flight& Flight::operator=(Flight& rightFlight)
{
    // Checking for self-assignment.
    if (this != &rightFlight)
    {
        // Assigning right flight members to this flight.
        this->m_passengers = rightFlight.m_passengers;
        this->m_fuel = rightFlight.m_fuel;
        strcpy(this->m_title, rightFlight.m_title);
        // Cleaning out the right flight.
        rightFlight.emptyPlane();
    }

    return *this;
}

Flight& Flight::operator=(const int rightOperand)
{
    // Checking for positive int and for the capacity limit.
    if (rightOperand > 0 && rightOperand <= Boen747Capacity)
    {
        // Assigning this flight passengers to the righthand int.
        this->m_passengers = rightOperand;
    }

    return *this;
}

Flight& Flight::operator=(const double rightOperand)
{
    // Checking for positive double and tank capacity limit.
    if (rightOperand > 0 && rightOperand < FuelTankCapacity)
    {
        // Assigning this fuel to the righthand double.
        this->m_fuel = rightOperand;
    }

    return *this;
}

Flight& Flight::operator+=(const double rightOperand)
{
    // Checking for negative double and full tank.
    if (rightOperand > 0.0 && m_fuel < FuelTankCapacity)
    {
        // Filling this tank with the righthand double.
        this->m_fuel += rightOperand;
    }

    return *this;
}

Flight& Flight::operator+=(const int rightOperand)
{
    // Checking for negative int and full flight.
    if (rightOperand > 0 && this->m_passengers < Boen747Capacity)
    {
        // Loading righthand int of passengers into this flight.
        this->m_passengers += rightOperand;
    }

    return *this;
}

Flight& Flight::operator-=(const double rightOperand)
{
    // Checking for negative double and correct max. amount to be reduced.
    if (rightOperand > 0.0 && rightOperand <= this->m_fuel)
    {
        // Pumping out the current fuel.
        this->m_fuel -= rightOperand;
    }

    return *this;
}

Flight& Flight::operator-=(const int rightOperand)
{
    // Checking for negative int and correct max. amount to be deplaned.
    if (rightOperand > 0 && rightOperand <= this->m_passengers)
    {
        // Deplaning the current passengers.
        this->m_passengers -= rightOperand;
    }

    return *this;
}

Flight& Flight::operator<<(Flight& rightFlight)
{
    // Checking for true flights and for no self-assignment.
    if (this && rightFlight && this->m_passengers != rightFlight.m_passengers)
    {
        // Calculating max. passengers per flight and moving.
        if (rightFlight.m_passengers + this->m_passengers <= Boen747Capacity)
        {
            this->m_passengers += rightFlight.m_passengers;
            // Remaining passengers in the right flight.
            rightFlight.m_passengers = 0;
        }
        else
        {
            rightFlight.m_passengers =
                (rightFlight.m_passengers + this->m_passengers) - Boen747Capacity;
            // Passengers boarded in the left (current) flight.
            this->m_passengers = Boen747Capacity;
        }
    }

    return *this;
}

Flight& Flight::operator>>(Flight& rightFlight)
{
    if (this && rightFlight && this->m_passengers != rightFlight.m_passengers)
    {
        if (rightFlight.m_passengers + this->m_passengers <= Boen747Capacity)
        {
            rightFlight.m_passengers += this->m_passengers;
            this->m_passengers = 0;
        }
        else
        {
            this->m_passengers =
                (rightFlight.m_passengers + this->m_passengers) - Boen747Capacity;
            rightFlight.m_passengers = Boen747Capacity;
        }
    }

    return *this;
}

int Flight::operator+(const Flight& rightFlight)
{
    int value = 0;

    // Checking for true flights.
    if (this && rightFlight)
    {
        // Assigning int to the sum of passengers.
        value = this->m_passengers + rightFlight.m_passengers;
    }

    return value;
}

// Binary helper operator.

int operator+=(int& leftOperand, const Flight& rightOperand)
{
    // Adding passengers to the left operand.
    leftOperand += rightOperand.m_passengers;

    return leftOperand;
}