#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>

const int Boen747Capacity = 388;
const int FuelTankCapacity = 238840;

class Flight {

    int m_passengers = 0;
    double m_fuel = 0;
    char m_title[16];
    void emptyPlane();

public:
    Flight();
    Flight(int passengers, double fuel, const char* title);
    std::ostream& display()const;
    // Type conversion operators.
    operator bool() const;
    operator int() const;
    operator double() const;
    operator const char* () const;
    // Unary operator.
    bool operator~() const;
    // Binary operators.
    Flight& operator=(Flight& rightFlight);
    Flight& operator=(const int rightOperand);
    Flight& operator=(const double rightOperand);
    Flight& operator+=(const double rightOperand);
    Flight& operator+=(const int rightOperand);
    Flight& operator-=(const double rightOperand);
    Flight& operator-=(const int rightOperand);
    Flight& operator<<(Flight& rightFlight);
    Flight& operator>>(Flight& rightFlight);
    int operator+(const Flight& rightFlight);
    // Binary helper operator.
    friend int operator+=(int& leftOperand, const Flight& rightOperand);
};
#endif // !FLIGHT_H