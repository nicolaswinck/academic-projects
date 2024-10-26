#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

class Person
{
public:
	virtual std::string status() const = 0;
	virtual std::string name() const = 0;
	virtual std::string age() const = 0;
	virtual std::string id() const = 0;
	virtual void display(std::ostream&) const = 0;

	virtual ~Person() = default;
};

#endif