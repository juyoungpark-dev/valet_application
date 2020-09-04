/* Citation and Sources...
Juyoung Park
150155182
-----------------------------------------------------------
I have done all the coding by myself and only copied the code  that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
#include "Menu.h"

namespace sdds
{
	//MenuItem:: ==================================
	MenuItem::MenuItem()
	{
		content = nullptr;
	}

	MenuItem::MenuItem(const char* content_)
	{
		content = nullptr;
		if (content_ != nullptr && content_[0] != '\0')
		{
			content = new char[std::strlen(content_) + 1];
			std::strcpy(content, content_);
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] content;
		content = nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& os)const
	{
		if (content != nullptr)
		{
			os << content << std::endl;
		}
		return os;
	}


	//Menu:: ==============================================
	Menu::Menu()
	{
		setEmpty();
	}

	Menu::Menu(const char* title_, int indent)
	{
		itemCount = 0;
		menuItems[0] = nullptr;
		if (title_ != nullptr && title_[0] != '\0')
		{
			menuTitle = new char[std::strlen(title_) + 1];
			std::strcpy(menuTitle, title_);
			indentation = indent;
		}
		else
		{
			setEmpty();
		}
	}

	Menu::Menu(const Menu& m)
	{
		setEmpty();
		*this = m; //call assign op
	}

	void Menu::setEmpty()
	{
		menuTitle = nullptr;
		menuItems[0] = nullptr;
		itemCount = 0;
		indentation = 0;
	}

	Menu& Menu::operator=(const Menu& m) //assign op (with Menu object)
	{
		if (this != &m)
		{
			if (m.menuTitle != nullptr)
			{
				delete[] menuTitle; //del prev dyn memory
				menuTitle = new char[std::strlen(m.menuTitle) + 1];
				std::strcpy(menuTitle, m.menuTitle);
				if (m.menuItems[0] != nullptr)
				{
					if (itemCount > 0)
					{
						for (int i = 0; i < this->itemCount; i++)
						{
							delete menuItems[i];
							menuItems[i] = nullptr;
						}
					}
					for (int i = 0;i < m.itemCount;i++)
					{
						menuItems[i] = new MenuItem(m.menuItems[i]->content);
					}
				}
				else
				{
					for (int i = 0; i < this->itemCount; i++)
					{
						delete menuItems[i];
						menuItems[i] = nullptr;
					}
				}
				itemCount = m.itemCount;
				indentation = m.indentation;
			}
			else
			{
				delete[] menuTitle;
				menuTitle = nullptr;
			}
		}
		return *this; //return copy-pasted current obj
	}

	Menu& Menu::operator=(const char* title) //assign op (with string)
	{
		if (std::strcmp(this->menuTitle, title) != 0)
		{
			if (title != nullptr && title[0] != '\0')
			{
				delete[] menuTitle; //del prev dyn memory
				menuTitle = new char[std::strlen(title) + 1];
				std::strcpy(menuTitle, title);
			}
			else
			{
				delete[] menuTitle;
				menuTitle = nullptr;
			}
		}
		return *this;
	}

	Menu::operator bool() const
	{
		//return true if it's not empty
		return !isEmpty();
	}

	bool Menu::isEmpty() const
	{
		//return true if it's empty
		return menuTitle == nullptr;
	}

	void Menu::display(std::ostream& os) const
	{
		if (isEmpty())
		{
			os << "Invalid Menu!" << std::endl;
		}
		else
		{
			for (int i = 0; i < indentation; i++)
			{
				os << "    "; //4 spaces for indentation
			}
			os << menuTitle << std::endl;
			if (!(itemCount > 0))
			{
				os << "No Items to display!" << std::endl;
			}
			else
			{
				for (int i = 0; i < itemCount; i++)
				{
					for (int i = 0; i < indentation; i++)
					{
						os << "    ";
					}
					os << i + 1 << "- " << menuItems[i]->content << std::endl;
				}
				for (int i = 0; i < indentation; i++)
				{
					os << "    ";
				}
				os << "> ";
			}
		}
	}


	void Menu::add(const char* item)
	{
		if (item != nullptr && item[0] != '\0')
		{
			//allocating memory to each index of the array 'menuItems', constructing MenuItem type at the same time.
			menuItems[itemCount] = new MenuItem(item);
			itemCount++;
		}
		else
		{
			delete[] menuTitle;
			menuTitle = nullptr;
		}

	}

	Menu& Menu::operator<<(const char* str)
	{
		add(str);
		return *this;
	}


	int Menu::run() const
	{
		std::string input;
		int selection = 0;
		bool done = false;

		display();

		if (itemCount > 0 && !isEmpty())
		{
			if (menuItems[0] != nullptr) //if any menuItem exists
			{
				std::getline(std::cin, input); //get input and store to string 'input'
				while (!done)	//while 'not done'
				{
					try
					{
						selection = std::stoi(input);
						done = true;
						if (done && selection > 0 && selection <= itemCount)
						{
							done = true;
						}
						else
						{
							std::cout << "Invalid selection, try again: ";
							done = false;
							std::getline(std::cin, input);
						}
					}
					catch (...) //if 'try' failed
					{
						std::cout << "Invalid Integer, try again: ";
						std::getline(std::cin, input);
					}
				}
			}
		}
		return selection;
	}

	Menu::operator int() const
	{
		return run();	//return the selected number of the menu
	}


	Menu::~Menu()
	{
		delete[] menuTitle;
		menuTitle = nullptr;
		for (int i = 0; i < itemCount; i++)
		{
			delete menuItems[i];
			menuItems[i] = nullptr;
		}
	}

}