#ifndef LINE_H
#define LINE_H
#include <iostream>
#include "LabelShape.h"

class Line : public LblShape
{
	int m_length;

public:
	Line();
	Line(const char* label, int length);
	// Functions that overrides the ones from the base class.
	void getSpecs(std::istream& istr);
	void draw(std::ostream& ostr) const;
};

#endif // !LINE_H