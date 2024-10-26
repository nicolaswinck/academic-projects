#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>

class Container
{
	// Set to 50 characters plus one null terminator byte.
	char m_content[50 + 1]{};
	int m_capacity;
	int m_volume;

protected:
	void setEmpty();
	int capacity() const;
	int volume() const;

public:
	Container(const char* content, int capacity, int volume = 0);
	int operator+=(int rhVolume);
	int operator-=(int rhVolume);
	operator bool() const;
	void clear(int capacity, const char* content);
	std::ostream& print(std::ostream& ostr) const;
	std::istream& read(std::istream& istr);
};

std::ostream& operator<<(std::ostream& ostr, const Container& con);
std::istream& operator>>(std::istream& istr, Container& con);
#endif // !CONTAINER_H