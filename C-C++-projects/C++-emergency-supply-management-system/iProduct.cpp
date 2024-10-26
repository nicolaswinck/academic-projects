#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <string.h>
#include "iProduct.h"

using namespace std;

std::ostream& operator<<(std::ostream& ostr, const iProduct& prod)
{
	return prod.display(ostr);
}

std::istream& operator>>(std::istream& istr, iProduct& prod)
{
	return prod.read(istr);
}