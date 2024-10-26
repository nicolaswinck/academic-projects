#ifndef MENU_H
#define MENU_H

class Menu
{
	char* m_content{};
	// Attribute for storing the number of items in a menu list.
	int m_numOptions;

public:
	Menu(const char* content);
	~Menu();
	Menu(const Menu& rm) = delete;
	Menu& operator=(const Menu& rm) = delete;
	unsigned int run();
};

#endif // !MENU_H