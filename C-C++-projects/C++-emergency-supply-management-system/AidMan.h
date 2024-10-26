#ifndef AIDMAN_H
#define AIDMAN_H

#include <iostream>
#include "Status.h"
#include "Menu.h"
#include "iProduct.h"

const int sdds_max_num_items = 100;

class AidMan
{
	char* m_fileName{};
	Menu m_mainMenu;
	iProduct* m_items[sdds_max_num_items];
	int m_numItems;
	unsigned int menu();

public:
	AidMan(const char* fileName = nullptr);
	~AidMan();
	AidMan(const AidMan&) = delete;
	AidMan& operator=(const AidMan&) = delete;
	void run();
	void save();
	void deallocate();
	bool load();
	int list(const char* sub_desc = nullptr);
	int search(int sku) const;
	void remove(int index);
};

#endif // !AIDMAN_H