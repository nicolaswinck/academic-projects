#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include "LabelShape.h"

class Rectangle : public LblShape
{
	int m_width;
	int m_height;

public:
	Rectangle();
	Rectangle(const char* label, int width, int height);
	// Functions that overrides the ones from the base class.
	void getSpecs(std::istream& istr);
	void draw(std::ostream& ostr) const;
};

#endif // !RECTANGLE_H