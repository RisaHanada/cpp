/***********************************************************************
// Billable Module
// File	Billable.cpp
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Billable.h"
#include "constants.h"
#include "Utils.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace seneca {

    /*
    Sets the base price of the item.
    */
	void Billable::price(double value) {
		m_price = value;
	}

    /*
    Sets the item’s name using dynamic memory allocation.
    */
	void Billable::name(const char* name) {
		delete[] m_name;
		m_name = nullptr;
		if (name != nullptr) {
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
		}
	}

    /*
    Initializes an empty Billable item
    */
	Billable::Billable() {
		m_name = nullptr;
		m_price = 0.0;
	}

    /*
    Copy constructor: Handles deep copies of dynamic members
    */
	Billable::Billable(const Billable& bill) {
		m_price = bill.m_price;
		if (bill.m_name != nullptr) {
			m_name = new char[strlen(bill.m_name) + 1];
			strcpy(m_name, bill.m_name);
		}
		else {
			m_name = nullptr;
		}
	}

    /*
    Copy assignment operator: Handles deep copies of dynamic members
    */
	Billable& Billable::operator=(const Billable& bill) {
		if (this != &bill) {
			delete[] m_name;
			m_price = bill.m_price;
			if (bill.m_name != nullptr) {
				m_name = new char[strlen(bill.m_name) + 1];
				strcpy(m_name, bill.m_name);
			}
			else {
				m_name = nullptr;
			}
		}
		return *this;
	}

    /*
    Releases dynamically allocated memory and ensures proper cleanup of derived objects.
    */
   	Billable::~Billable() {
		delete[] m_name;
		m_name = nullptr;
	}

    /*
    Returns the item’s price. Derived classes may override to adjust pricing.
    */
	double Billable::price() const {
		return m_price;
	}
	
    /*
    Adds the item’s price to a running total (double).
    */
	double operator+(double money, const Billable& B) {
		return money + B.price();
	}

    /*
    Adds the item’s price to a running total (double).
    */
	double& operator+=(double& money, const Billable& B) {
		return money += B.price();
	}

    /*
    Returns the item’s name for display or comparison.
    */
	Billable::operator const char* ()const {
		return m_name;
	}
}