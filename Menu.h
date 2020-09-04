//Juyoung Park 150155182
//Menu.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#include <iostream>

#ifndef _SDDS_MENU_H
#define _SDDS_MENU_H
namespace sdds
{

	const int MAX_NO_OF_ITEMS = 10;

	class Menu; //forward declare to be a friend of MenuItem

	class MenuItem //fully private calss;
	{
		friend class Menu;

		char* content;

		MenuItem(); //default constr
		MenuItem(const char*); //set constr
		std::ostream& display(std::ostream& os = std::cout)const;
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		~MenuItem(); //destr
	};

	class Menu
	{
		char* menuTitle;
		MenuItem* menuItems[MAX_NO_OF_ITEMS]; //arary of pointers; each element is an address of pointed menuItem
		int itemCount;
		int indentation; //level 1 -> 4spaces to the right

	public:
		Menu(); //default constr
		Menu(const char* title_, int indent = 0); //set constr
		Menu(const Menu&); //copy constr
		Menu& operator=(const Menu&); //assignment op
		Menu& operator=(const char*);
		~Menu();
		void setEmpty();
		operator bool() const; //bool cast
		bool isEmpty() const;
		void display(std::ostream& os = std::cout) const;
		void add(const char*);
		Menu& operator<<(const char*);
		int run() const; //displays the Menu and waits for the user's response to select an option
		operator int() const;
	};
}

#endif