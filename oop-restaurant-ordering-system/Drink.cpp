/***********************************************************************
// Drink Module
// File	Drink.cpp
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
namespace seneca {
    /*
    Displays drink name, size (SML.. / MID.. / LRG.. / XLR..), and price in formatted columns.
	*/
    ostream& Drink::print(ostream& ostr)const {
		ostr.setf(ios::left);
		ostr.width(28);
		ostr.fill('.');
		ostr << (const char*)(*this);
		ostr.unsetf(ios::left);

		if (!(ordered())) {
			ostr << ".....";
		}
		else if (m_size == 'S') {
			ostr << "SML..";
		}
		else if (m_size == 'M') {
			ostr << "MID..";
		}
		else if (m_size == 'L') {
			ostr << "LRG..";
		}
		else if (m_size == 'X') {
			ostr << "XLR..";
		}
		ostr.setf(ios::right);
		ostr.width(7);
		ostr.fill(' ');
		ostr.setf(ios::fixed);
		ostr.precision(2);
		ostr << price();
		ostr.unsetf(ios::right);
		return ostr;
	}

    /*
    Shows a drink-size menu and sets the selected size. Returns true if ordered.
    */
	bool Drink::order() {
		int menuNum;
		cout << "         Drink Size Selection" << endl;
		cout << "          1- Small" << endl;
		cout << "          2- Medium" << endl;
		cout << "          3- Larg" << endl;
		cout << "          4- Extra Large" << endl;
		cout << "          0- Back" << endl;
		cout << "         > ";
		cin >> menuNum;

		if (menuNum == 1) {
			m_size = 'S';
		}
		else if (menuNum == 2) {
			m_size = 'M';
		}
		else if (menuNum == 3) {
			m_size = 'L';
		}
		else if (menuNum == 4) {
			m_size = 'X';
		}
		else if (menuNum == 0) {
			m_size = '\0';
			return false;
		}else{
			cin.clear();
			cin.ignore(10000, '\n');
			return false;
		}
		return true;
	}

    /*
    Returns true if a size has been selected.
    */
	bool Drink::ordered()const {
		return (m_size == 'S' || m_size == 'M' || m_size == 'L' || m_size == 'X');
	}

    /*
    Reads drink name and base price from a CSV file.
    */
	ifstream& Drink::read(ifstream& file) {
		if (!file.is_open()) {
			cerr << "File is not open" << endl;
			return file;
		}
		char name[25];
		double p;
		if (!file.getline(name, 25, ',')) {
			return file;
		}
		if (!(file >> p)) {
			return file;
		}
		file.ignore(10000, '\n');

		Billable::name(name);
		Billable::price(p);
		m_size = '\0';
		return file;
	}
	
    /*
    Adjusts price based on size:
    - Small:50%
    - Medium:75%
    - Large:100%
    - Extra Large:150%
    */
	double Drink::price() const {
		double p;
		if (m_size == 'L' || m_size == '\0') {
			p = Billable::price();
		}
		else if (m_size == 'S') {
			p = Billable::price() * 0.5;
		}
		else if (m_size == 'M') {
			p = Billable::price() * 3 / 4;
		}
		else if (m_size == 'X') {
			p = Billable::price() * 1.5;
		}
		return p;
	}
}