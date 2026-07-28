/***********************************************************************
// Menu Module
// File	Menu.h
// Date	2025/11/2
// Author Risa Hanada
***********************************************************************/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca {
	class Menu;

	class MenuItem {
		char* item; // dynamically allocated menu content
		unsigned int n; // number of indentations
		unsigned int size; // size of each indentation
		int number; // row number (used for numbered menu items)

        // constructors
		MenuItem();
		MenuItem(const char* content, unsigned int numOfInd, unsigned int sizeOfInd, int rowNum);
		
        // copying disabled to prevent accidental DMA copying
		MenuItem(const MenuItem& mi) = delete;
		MenuItem& operator=(const MenuItem& mi) = delete;

        // destructor
        ~MenuItem();

        // bool conversion
		operator bool() const;

        // displays the MenuItem
		std::ostream& display(std::ostream& ostr = std::cout) const;

        // grant Menu full access to MenuItem's private members
        // allows Menu to manage MenuItem objects internally while preventing access from any other class
		friend class Menu;
	};

	class Menu {
		unsigned int mNum; // indentation number for MenuItem objects
		unsigned int mSize; // indentation size for MenuItem objects
		unsigned int mNumber; // number of MenuItem objects currently stored

		MenuItem mTitle; // title
		MenuItem mExit;  // exit option
		MenuItem mEntry; // selection prompt
		MenuItem* menuItem[MaximumNumberOfMenuItems]; // array of MenuItem pointers (composition)
	public:
        // constructor
		Menu(const char* title, const char* exit = "Exit", unsigned int numInd = 0, unsigned int sizeInd = 3);
		
        // copying disabled
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
        
        // destructor
		~Menu();
        
        // adds a new MenuItem dynamically using << operator
        Menu& operator<<(const char* content);
        
        // displays menu and returns user selection
		size_t select() const;
        
        // insertion operator: displays menu if ostream is cout, and returns user selection
		friend size_t operator<<(std::ostream& ostr, const Menu& m);
	};
	
}

#endif