#ifndef LABELCREATOR_H
#define LABELCREATOR_H

#include "Label.h"

class LabelMaker
{
	Label* m_listOfLabels = { 0 };
	int m_limitLabels;

public:
	LabelMaker();
	LabelMaker(int noOfLabels);
	void readLabels();
	void printLabels();
	~LabelMaker();
};

#endif // !LABELCREATOR_H