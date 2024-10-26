#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
#include "Menu.h"
#include "Item.h"
#include "Perishable.h"

using namespace std;

unsigned int AidMan::menu()
{
	// Variables to store the current date and then print it.
	int year;
	int month;
	int day;
	// Getting the current date and assigning to the variables' addresses.
	ut.getSystemDate(&year, &month, &day);
	// Printing out the current date with leading zeros.
	cout << "Aid Management System" << endl;
	cout << "Date: " << year << '/';
	cout.fill('0');
	cout.width(2);
	cout << month << '/';
	cout.fill('0');
	cout.width(2);
	cout << day << endl;
	// Displaying file name.
	if (m_fileName == nullptr)
	{
		cout << "Data file: No file" << endl;
	}
	else
	{
		cout << "Data file: " << m_fileName << endl;
	}

	std::cout << "---------------------------------" << endl;

	return m_mainMenu.run();
}

AidMan::AidMan(const char* fileName) :
	m_fileName(nullptr),
	m_mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database")
{
	m_numItems = 0;

	for (int i = 0; i < sdds_max_num_items; ++i)
	{
		m_items[i] = nullptr;
	}

	if (fileName)
	{
		// Dynamically assigning the given name to the attribute.
		ut.alocpy(m_fileName, fileName);
	}
}

AidMan::~AidMan()
{
	delete[] m_fileName;
	m_fileName = nullptr;

	for (int i = 0; i < m_numItems; ++i)
	{
		delete m_items[i];
		m_items[i] = nullptr;
	}
}

void AidMan::run()
{
	// Exit flag.
	int exit = 0;
	// Input for file name (menu case 1).
	char inputFileName[1000];
	// Input for description search on list (menu case 3).
	char inputDescr[1000];
	// Index result from sku query (menu case 3).
	int foundSku;
	// File for shipping (menu case 6).
	ofstream shippingFile("shippingOrder.txt");
	// Variables for storing the current date (menu case 6).
	int year, month, day;
	// Counting the number of shipping items (menu case 6).
	int shippingCount = 0;

	do {
		// Option entered by the user from the menu.
		unsigned int choice = menu();

		// Forcing option 7 if there's no filename entered.
		if (m_fileName == nullptr && choice != 0 && choice != 7)
		{
			choice = 7;
		}

		switch (choice)
		{
		case 1:
			cout << endl;
			cout << "****List Items****" << endl;

			if (list())
			{
				int inputRow = 0;
				cout << "Enter row number to display details or <ENTER> to continue:" << endl;
				cout << "> ";
				// Checking if the next character is a newline char.
				if (cin.peek() != '\n')
				{
					inputRow = ut.getInt(1, m_numItems);
				}
				// Displaying item details in non-linear format.
				if (inputRow)
				{
					m_items[inputRow - 1]->linear(false);
					m_items[inputRow - 1]->display(cout);
					cout << endl;
				}
			}

			break;

		case 2:
			cout << endl;
			cout << "****Add Item****" << endl;
			// Checking for number of items (max 100).
			if (m_numItems >= sdds_max_num_items)
			{
				cout << "Database full!" << endl;
			}
			// Slots available.
			else
			{
				int inputOption = 0;
				int inputSku = 0;

				cout << "1- Perishable" << endl;
				cout << "2- Non-Perishable" << endl;
				cout << "-----------------" << endl;
				cout << "0- Exit" << endl;
				cout << "> ";
				// Prompting user for perishable or non-perishable.
				inputOption = ut.getInt(0, 2);
				// Exit case.
				if (inputOption == 0)
				{
					cout << "Aborted" << endl;
				}
				// Perishable case.
				if (inputOption == 1)
				{
					// Allocating memory for new perishable item.
					Perishable* newPerishable = new Perishable();
					// Reading SKU number from user.
					inputSku = newPerishable->readSku(cin);
					// The SKU is already taken.
					if (search(inputSku) >= 0)
					{
						cout << "Sku: " << inputSku << " is already in the system, try updating quantity instead." << endl;
						delete newPerishable;
					}
					// The SKU is NOT taken already.
					else
					{
						// Reading the remaining data.
						newPerishable->read(cin);
						// Using bool operator overload to check the new perishable state.
						if (newPerishable->operator bool())
						{
							// Good state: copy to item pointer.
							m_items[m_numItems] = newPerishable;
							m_numItems++;
						}
						else
						{
							// Bad state: displaying and deleting.
							newPerishable->display(cout);
							delete newPerishable;
						}
					}
				}
				if (inputOption == 2)
				{
					// Allocating memory for new non-perishable item.
					// (Same procedure as option 1, but with Item class.)
					Item* newItem = new Item();

					inputSku = newItem->readSku(cin);

					if (search(inputSku) >= 0)
					{
						cout << "Sku: " << inputSku << " is already in the system, try updating quantity instead." << endl;
						delete newItem;
					}
					else
					{
						newItem->read(cin);
						if (newItem->operator bool())
						{
							m_items[m_numItems] = newItem;
							m_numItems++;
						}
						else
						{
							newItem->display(cout);
							delete newItem;
						}
					}
				}
			}

			break;

		case 3:
			cout << endl;
			cout << "****Remove Item****" << endl;
			// Getting input for description query.
			cout << "Item description: ";
			cin >> inputDescr;
			cin.ignore(1000, '\n');
			// Assigning number of matches.
			foundSku = list(inputDescr);
			// Matches are found.
			if (foundSku)
			{
				// Prompting user for SKU.
				cout << "Enter SKU: ";
				int inputRemoveSku = ut.getInt(10000, 99999);
				// Searching for SKU.
				int skuFound = search(inputRemoveSku);
				// No matches for SKU number.
				if (skuFound < 0)
				{
					cout << "SKU not found!" << endl;
				}
				// Found matches.
				else
				{
					cout << "Following item will be removed: " << endl;

					// Displaying result in non-linear format.
					m_items[skuFound]->linear(false);
					m_items[skuFound]->display(cout) << endl;

					cout << "Are you sure?" << endl;
					cout << "1- Yes!" << endl;
					cout << "0- Exit" << endl;
					cout << "> ";

					int inputDeleteOption = ut.getInt(0, 1);
					// Removing item from list.
					if (inputDeleteOption == 1)
					{
						remove(skuFound);
						cout << "Item removed!" << endl;
					}
					else
					{
						cout << "Aborted!" << endl;
					}
				}
			}
			else
			{
				cout << "No matches found!" << endl;
			}

			break;

		case 4:
			cout << endl;
			cout << "****Update Quantity****" << endl;
			// Getting input for description query.
			cout << "Item description: ";
			cin >> inputDescr;
			cin.ignore(1000, '\n');
			// Assigning number of matches.
			foundSku = list(inputDescr);

			if (foundSku)
			{
				// Prompting user for SKU.
				cout << "Enter SKU: ";
				int inputRemoveSku = ut.getInt(10000, 99999);
				// Searching for SKU.
				int skuFound = search(inputRemoveSku);
				// No matches for SKU number.
				if (skuFound < 0)
				{
					cout << "SKU not found!" << endl;
				}
				// Found matches.
				else
				{
					cout << "1- Add" << endl;
					cout << "2- Reduce" << endl;
					cout << "0- Exit" << endl;
					cout << "> ";

					int inputUpdateOption = ut.getInt(0, 2);
					// Adding quantity.
					if (inputUpdateOption == 1)
					{
						// Checking if quantity is not already fullfilled (using queries).
						if (m_items[skuFound]->qty() < m_items[skuFound]->qtyNeeded())
						{
							cout << "Quantity to add: ";
							// Input for quantity to add (from 1 up to the difference).
							int inputToAdd = ut.getInt(1, m_items[skuFound]->qtyNeeded() - m_items[skuFound]->qty());
							// Adding chosen quantity (using operator).
							m_items[skuFound]->operator+=(inputToAdd);
							cout << inputToAdd << " items added!" << endl;
						}
						// We have everything we need!
						else
						{
							cout << "Quantity Needed already fulfilled!" << endl;
						}
					}
					// Reducing quantity.
					if (inputUpdateOption == 2)
					{
						// Checking if quantity is not zero.
						if (m_items[skuFound]->qty() > 0)
						{
							cout << "Quantity to reduce: ";
							// Input for quantity to be reduced (from 1 up to the total on hand).
							int inputToReduce = ut.getInt(1, m_items[skuFound]->qty());
							// Reducing from chosen quantity (using operator).
							m_items[skuFound]->operator-=(inputToReduce);
							cout << inputToReduce << " items removed!" << endl;
						}
						else
						{
							cout << "Quaintity on hand is zero!" << endl;
						}
					}
					if (inputUpdateOption == 0)
					{
						cout << "Aborted!" << endl;
					}
				}
			}
			else
			{
				cout << "No matches found!" << endl;
			}

			break;

		case 5:
			cout << endl;
			cout << "****Sort****" << endl;

			// The following algorithm is a simple bubble sort.
			// First general loop. 
			for (int i = 0; i < m_numItems; i++)
			{
				// Nested loop to compare the items after the current item.
				for (int j = i + 1; j < m_numItems; j++)
				{
					// Checking for the smallest quantity difference in the pair.
					if (m_items[i]->qtyNeeded() - m_items[i]->qty() <
						m_items[j]->qtyNeeded() - m_items[j]->qty())
					{
						// Swapping items (passing through temporary item).
						iProduct* temp = m_items[i];
						m_items[i] = m_items[j];
						m_items[j] = temp;
					}
				}
			}

			cout << "Sort completed!" << endl;

			break;

		case 6:
			cout << endl;
			cout << "****Ship Items****" << endl;
			// Getting system date.
			ut.getSystemDate(&year, &month, &day);
			// Printing system date to the file.
			shippingFile << "Shipping Order, Date: ";
			shippingFile << year << '/';
			shippingFile.fill('0');
			shippingFile.width(2);
			shippingFile << month << '/';
			shippingFile.fill('0');
			shippingFile.width(2);
			shippingFile << day << endl;

			// Formatting the header similar to the list() function.
			// Printing it to the file.
			shippingFile << left;
			shippingFile.fill(' ');
			shippingFile << setw(4) << " ROW" << " | ";
			shippingFile << setw(5) << " SKU" << " | ";
			shippingFile << setw(35) << "Description" << " | ";
			shippingFile << setw(4) << "Have" << " | ";
			shippingFile << setw(4) << "Need" << " | ";
			shippingFile << setw(7) << " Price" << " | ";
			shippingFile << "Expiry" << endl;

			shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			for (int i = 0; i < m_numItems; i++)
			{
				if (m_items[i]->qty() == m_items[i]->qtyNeeded())
				{
					// Counting only the matching items.
					shippingCount++;
					// Printing adjusted row number.
					shippingFile << right << setw(4) << shippingCount << " | ";
					// Adjusting linear flag.
					m_items[i]->linear(true);
					m_items[i]->display(shippingFile) << endl;
					// Removing item from the general list.
					remove(i);
				}
			}

			shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
			cout << "Shipping Order for " << shippingCount << " times saved!" << endl;
			shippingFile.close();

			break;

		case 7:
			cout << endl;
			cout << "****New/Open Aid Database****" << endl;
			// Prompting for filename.
			cout << "Enter file name: ";
			cin >> inputFileName;
			// Deallocating.
			if (m_fileName != nullptr)
			{
				delete[] m_fileName;
				m_fileName = nullptr;
			}

			ut.alocpy(m_fileName, inputFileName);

			if (load())
			{
				cout << m_numItems << " records loaded!" << endl;
			}
			else
			{
				cout << "Failed to load data." << endl;
			}

			break;

		case 0:
			cout << "Exiting Program!";
			exit = 1;
			break;
		}
		cout << endl;

	} while (!exit);

	// Saving the records into the file.
	save();
	deallocate();
}

void AidMan::save()
{
	if (m_fileName != nullptr)
	{
		// Creating ofstream object with the name of the file to be written into.
		ofstream file(m_fileName);

		if (file.is_open())
		{
			for (int i = 0; i < m_numItems; i++)
			{
				// Saving the iProduct items as records into the file.
				// Separating each iProduct item with newline.
				if (m_items[i] != nullptr)
				{
					m_items[i]->save(file);
					file << endl;
				}
			}
		}
		// Closing file.
		file.close();
	}
}

void AidMan::deallocate()
{
	// Deallocating the iProduct items.
	for (int i = 0; i < m_numItems; i++)
	{
		delete m_items[i];
		m_items[i] = nullptr;
	}
	// Deallocating the other attributes.
	delete[] m_fileName;
	m_fileName = nullptr;
	m_numItems = 0;
}

bool AidMan::load()
{
	// Result flag to avoid more than one exit for the function.
	bool result = false;
	bool exit = 0;
	int selection = 0;
	char firstChar = '\0';

	// Opening m_fileName into ifstream.
	std::ifstream file(m_fileName);
	// Case for file opening not successful.
	if (!file)
	{
		cout << "Failed to open " << m_fileName << " for reading!" << endl;
		cout << "Would you like to create a new data file?" << endl;
		cout << "1- Yes!" << endl;
		cout << "0- Exit" << endl;
		cout << "> ";
		// Prompting 0 or 1 (foolproof).
		selection = ut.getInt(0, 1);
		while (!exit)
		{
			if (selection == 1)
			{
				// Opening a new blank file.
				ofstream newFile(m_fileName);
				if (newFile)
				{
					cout << "Empty file " << m_fileName << " created!" << endl;
				}
				else
				{
					cout << "Failed to create new empty file." << endl;
				}
				exit = 1;
			}
			else
			{
				exit = 1;
			}
		}
	}
	// Reading the file until end.
	while (!file.eof() && !exit)
	{
		// Peeking first character to decide whether the product is Item or Perishable.
		firstChar = file.peek();
		// The character is a digit.
		if (isdigit(firstChar))
		{
			// The digit is 1, 2 or 3, indicating Perishable.
			if (firstChar == '1' || firstChar == '2' || firstChar == '3')
			{
				m_items[m_numItems] = new Perishable();
			}
			// Is not Perishable.
			else
			{
				m_items[m_numItems] = new Item();
			}

			if (m_items[m_numItems]->load(file))
			{
				// Checking for the item state (is null, and has SKU or has description).
				if (m_items[m_numItems]->operator bool() == true)
				{
					// Incrementing by one.
					m_numItems++;
					result = true;
				}
				else
				{
					delete m_items[m_numItems];
				}
			}
			else
			{
				delete m_items[m_numItems];
			}
		}
		// First digit is different from a number (not an SKU): fail.
		else
		{
			file.setstate(ios::failbit);
		}
	}
	// Closing file.
	file.close();

	return result;
}

int AidMan::list(const char* sub_desc)
{
	// Variable for the total number of printed items.
	int printedItems = 0;

	// Formatting the header similar to the item classes.
	cout << left;
	cout.fill(' ');
	cout << setw(4) << " ROW" << " | ";
	cout << setw(5) << " SKU" << " | ";
	cout << setw(35) << "Description" << " | ";
	cout << setw(4) << "Have" << " | ";
	cout << setw(4) << "Need" << " | ";
	cout << setw(7) << " Price" << " | ";
	cout << "Expiry" << endl;

	cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
	// Printing all items in linear formatting.
	if (sub_desc == nullptr)
	{
		for (int i = 0; i < m_numItems; i++)
		{
			// Printing row number.
			cout << right << setw(4) << i + 1 << " | ";
			// Adjusting linear flag.
			m_items[i]->linear(true);
			m_items[i]->display(cout) << endl;
			printedItems++;
		}
	}
	// Printing only the items which contain the sub_desc.
	else
	{
		for (int i = 0; i < m_numItems; i++)
		{
			// Using the == operator overload to fetch items.
			if (m_items[i]->operator==(sub_desc))
			{
				cout << right << setw(4) << i + 1 << " | ";
				m_items[i]->linear(true);
				m_items[i]->display(cout) << endl;
				printedItems++;
			}
		}
	}
	// Showing empty list.
	if (printedItems <= 0)
	{
		cout << "The list is empty!" << endl;
	}

	cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

	return printedItems;
}

int AidMan::search(int sku) const
{
	// Match holder: default is no match (-1).
	int match = -1;

	for (int i = 0; i < m_numItems; i++)
	{
		// If match is found, the index is assigned.
		if (m_items[i]->operator==(sku))
		{
			match = i;
		}
	}

	return match;
}

void AidMan::remove(int index)
{
	// Deleting item pointer from the array.
	delete m_items[index];
	// Shifting products to left.
	for (int i = index; i < m_numItems - 1; i++)
	{
		m_items[i] = m_items[i + 1];
	}
	// Reducing number of items by one.
	m_numItems--;
}