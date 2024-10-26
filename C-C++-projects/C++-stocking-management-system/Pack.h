#ifndef PACK_H
#define PACK_H
#include <iostream>
#include "Container.h"

class Pack : public Container
{
	int m_unitSize;

public:
	Pack(const char* content, int size, int unitSize = 330, int numUnits = 0);
	int operator+=(int rhNumUnits);
	int operator-=(int rhNumUnits);
	int unit() const;
	int noOfUnits() const;
	int size() const;
	void clear(int packSize, int unitSize, const char* content);
	std::ostream& print(std::ostream& ostr) const;
	std::istream& read(std::istream& istr);
};

std::ostream& operator<<(std::ostream& ostr, const Pack& pk);
std::istream& operator>>(std::istream& istr, Pack& pk);

#endif // !PACK_H