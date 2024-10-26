#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

class Shape
{
public:
	virtual void draw(std::ostream& ostr) const = 0;
	virtual void getSpecs(std::istream& istr) = 0;
	// Virtual empty destructor.
	virtual ~Shape() {};
};
// Helper functions (insertion and extraction operators).
std::ostream& operator<<(std::ostream& ostr, const Shape& shape);
std::istream& operator>>(std::istream& istr, Shape& shape);

#endif // !SHAPE_H