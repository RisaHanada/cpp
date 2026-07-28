/***********************************************************************
// Menu Module
// File	Menu.cpp
// Date	2025/11/2
// Author Risa Hanada
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "constants.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

namespace seneca {
    /*
    Sets a safe empty state
    */
	MenuItem::MenuItem() {
		item = nullptr;
		n = 0;
		size = 0;
		number = -1;
	}

    /*
    Creates a MenuItem using the provided content, indentation count, indentation size, and row number.
    If any value is invalid (empty content, excessive indentation, invalid row), the object is set to a safe empty state.
    */
	MenuItem::MenuItem(const char* content, unsigned int numOfInd, unsigned int sizeOfInd, int rowNum) {
		if (content && numOfInd <= 4 && sizeOfInd <= 4 && rowNum <= (int)MaximumNumberOfMenuItems && rowNum >= -1) {
			item = new char[strlen(content) + 1];
			strcpy(item, content);
			n = numOfInd;
			size = sizeOfInd;
			number = rowNum;
		}
		else {
			item = nullptr;
			n = 0;
			size = 0;
			number = -1;
		}
	}

    /*
    Releases dynamically allocated memory used for storing the MenuItem content.
    */
	MenuItem::~MenuItem() {
		delete[] item;
		item = nullptr;
	}

    /*
    Returns true if the MenuItem is valid (content exists), otherwise returns false.
    */
	MenuItem::operator bool() const {
		return item != nullptr;
	}

    /*
    Outputs the MenuItem in formatted form:
    - Applies indentation
    - Prints row number (if non-negative)
    - Skips leading whitespace in content
    If the MenuItem is invalid, prints "??????????".
    */
	ostream& MenuItem::display(ostream& ostr) const {
		if (item != nullptr) {
			
			for (unsigned int i = 0; i < n * size;++i) {
				ostr << ' ';
			}
			if (number >= 0) {
				ostr.width(2);
				ostr.setf(ios::right);
				ostr << number << "- ";
				ostr.unsetf(ios::right);
			}
			
			const char* content = item;
			while (*content == ' ' || *content == '\t' || *content == '\n' || *content == '\v' || *content == '\r' || *content == '\f') {
				content++;
			}
			ostr << content;
		}
		else
		{
			ostr << "??????????";
		}
		return ostr;
	}

    /*
    nitializes the Menu with a title, an exit option, indentation settings, and a selection prompt.
    Sets all MenuItem pointers in the internal array to nullptr.
    */
	Menu::Menu(const char* title, const char* exit, unsigned int numInd, unsigned int sizeInd) 
		:mNum(numInd), mSize(sizeInd), mNumber(0), mTitle(title, numInd, sizeInd, -1), mExit(exit, numInd, sizeInd, 0), mEntry(">", numInd, sizeInd, -1){
		for (unsigned int i = 0;i < MaximumNumberOfMenuItems;i++) {
			menuItem[i] = nullptr;
		}
	}

    /*
    Adds a new MenuItem dynamically to the Menu using the provided content.
    Automatically assigns the correct row number. 
    */
	Menu& Menu::operator<<(const char* content) {
		if (mNumber < MaximumNumberOfMenuItems && content) {
			menuItem[mNumber] = new MenuItem(content, mNum, mSize, mNumber + 1);
			mNumber++;
		}
		return *this;
	}

    /*
    Iterates through all MenuItem pointers, deletes allocated MenuItem objects, and sets pointers to nullptr.
    */
	Menu::~Menu() {
		for (unsigned int i = 0;i < MaximumNumberOfMenuItems;i++) {
			delete menuItem[i];
			menuItem[i] = nullptr;
		}
	}

    /*
    Displays the entire menu:
    - Title
    - All MenuItem entries
    - Exit option
    - Selection prompt
    Then obtains a validated integer input from the user and returns the selected option.
    */
	size_t Menu::select() const {
		if (mTitle) {
			mTitle.display() << endl;
		}
		for (unsigned int i = 0; i < mNumber; i++) {
			menuItem[i]->display() << endl;
		}
		mExit.display() << endl;
		mEntry.display();
		cout << ' ';
		int select = getInt(0, (int)mNumber);
		return (size_t)select;
	}

    /*
    If ostr is cout, displays the menu and returns the user’s selection.
    If ostr is not cout, returns 0 without performing selection.
    */
	size_t operator<<(ostream& ostr, const Menu& m) {
		if (&ostr == &cout) {
			return m.select();
		}
		else {
			return 0;
		}
	}
}