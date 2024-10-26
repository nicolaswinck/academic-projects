#ifndef LABELSHAPE_H
#define LABELSHAPE_H
#include <iostream>
#include "Shape.h"

#define LABEL_SIZE 50

class LblShape : public Shape
{
	char* m_label = nullptr;

protected:
	// Query to return the label value by the derived functions.
	const char* label() const;
public:
	LblShape();
	LblShape(const char* label);
	virtual ~LblShape();
	// Deleted actions.
	LblShape(const LblShape& rbs) = delete;
	LblShape& operator=(const LblShape& rbs) = delete;
	// Function to override the pure virtual function.
	void getSpecs(std::istream& istr);
};

#endif // !LABELSHAPE_H