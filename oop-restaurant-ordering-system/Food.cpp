/***********************************************************************
// Food Module
// File	Food.cpp
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Food.h"
#include "Billable.h"
#include "constants.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;
namespace seneca {
    /*
    Sets a safe empty state
    */
	Food::Food() {
		m_customize = nullptr;
		m_ordered = false;
		m_child = false;
	}

    /*
    Copy constructor: Handles deep copies of dynamic members
    */
	Food::Food(const Food& food) :Billable(food), m_ordered(food.m_ordered), m_child(food.m_child), m_customize(nullptr)
	{
		m_ordered = food.m_ordered;
		m_child = food.m_child;
		if (food.m_customize != nullptr) {
			m_customize = new char[strlen(food.m_customize) + 1];
			strcpy(m_customize, food.m_customize);
		}
		else {
			m_customize = nullptr;
		}
	}

    /*
    Copy assignment operator: Handles deep copies of dynamic members
    */
   	Food& Food::operator=(const Food& food) {
		if (this != &food) {
			delete[] m_customize;
			Billable::operator=(food);
			m_ordered = food.m_ordered;
			m_child = food.m_child;
			if (food.m_customize != nullptr) {
				m_customize = new char[strlen(food.m_customize) + 1];
				strcpy(m_customize, food.m_customize);
			}
			else {
				m_customize = nullptr;
			}
		}
		return *this;
	}

    /*
    Releases dynamically allocated memory used for m_customize
    */
    Food::~Food() {
		delete[] m_customize;
		m_customize = nullptr;
	}

    /*
    Displays food name, portion type (Adult / Child / .....), price, and customizations (only when printing to cout).
    */
	std::ostream& Food::print(std::ostream& ostr)const {
		ostr.setf(ios::left);
		ostr.width(28);
		ostr.fill('.');
		ostr << (const char*)(*this);
		ostr.unsetf(ios::left);

		if (ordered()) {
			if (m_child) {
				ostr << "Child";
			}
			else {
				ostr << "Adult";
			}
		}
		else {
			ostr << ".....";
		}

		ostr.setf(ios::right);
		ostr.width(7);
		ostr.fill(' ');
		ostr.setf(ios::fixed);
		ostr.precision(2);
		ostr << price();
		ostr.unsetf(ios::right);

		if (m_customize != nullptr && &ostr == &cout) {
			ostr << " >> ";
			for (int i = 0; i < 30 && m_customize[i] != '\0'; i++) {
				ostr << m_customize[i];
			}
		}
		return ostr;
	}

    /*
    Prompts user to select Adult or Child portion.
    If ordered, asks for customization notes.
    Returns true if portion selected.
    */
	bool Food::order() {
		int selectSize;
		cout << "         Food Size Selection" << endl;
		cout << "          1- Adult" << endl;
		cout << "          2- Child" << endl;
		cout << "          0- Back" << endl;
		cout << "         > ";
		cin >> selectSize;
		cin.ignore(10000, '\n');

		if (selectSize == 1) {
			m_ordered = true;
			m_child = false;
		}
		else if(selectSize == 2){
			m_ordered = true;
			m_child = true;
		}
		else if (selectSize == 0) {
			m_ordered = false;
			m_child = false;
			delete[] m_customize;
			m_customize = nullptr;
			return false;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			return false;
		}

		if (m_ordered) {
			cout << "Special instructions" << endl;
			cout << "> ";
			string custom;
			getline(cin, custom);

			delete[] m_customize;
			if (custom.empty()) {
				m_customize = nullptr;
			}
			else {
				ut.alocpy(m_customize, custom.c_str());
			}

			return true;
		}
		else {
			return false;
		}
	}

    /*
    Returns true if a portion has been selected.
    */
	bool Food::ordered()const {
		return m_ordered;
	}

    /*
    Reads food name and price from a CSV file.
    Resets portion and customization
    */
	std::ifstream& Food::read(std::ifstream& file) {
		if (!file.is_open()) {
			cerr << "File is not open" << endl;
			return file;
		}
		char name[25];
		double p;
		if(!file.getline(name, 25, ',')) {
			return file;
		}
		if (!(file >> p)) {
			return file;
		}
		file.ignore(10000, '\n');

		Billable::name(name);
		Billable::price(p);
		m_ordered = false;
		m_child = false;
		delete[] m_customize;
		m_customize = nullptr;
		return file;
	}

    /*
    Returns half price for child portions; otherwise returns base price.
    */
	double Food::price() const {
		if(!ordered()){
			return Billable::price();
		}
		else if (m_child) {
			return Billable::price() / 2;
		}
		else {
			return Billable::price();
		}
	}
}
