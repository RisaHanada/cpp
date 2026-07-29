/***********************************************************************
// Billable Module
// File	Billable.h
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#pragma once
#ifndef BILLABLE_H
#define BILLABLE_H
#include <iostream>
#include <fstream>
using namespace std;
namespace seneca {
	class Billable {
		char* m_name; //dynamically allocated item name
		double m_price; // base price
	protected:
		void price(double value); // sets the item's price
		void name(const char* name); // sets the item's name (dynamic allocation)
	public:
        // constructor
		Billable();
        // copy constructor
		Billable(const Billable& bill);
        // copy assignment operator
		Billable& operator=(const Billable& bill);
        // virtual destructor
		virtual ~Billable();

        // returns the item's price (may be overridden)
		virtual double price() const;

        // pure virtual (prints formatted item information)
		virtual std::ostream& print(std::ostream& ostr = cout)const = 0;
        // pure virtual (prompts user to order item details)
		virtual bool order() = 0;
        // pure virtual (returns true if item has been ordered)
		virtual bool ordered()const = 0;
        // pure virtual (reads item details from file)
		virtual std::ifstream& read(std::ifstream& file) = 0;

        // Adds item price to a double 
		friend double operator+(double money, const Billable& B);
        // adds item price to a double 
		friend double& operator+=(double& money, const Billable& B);
        
        // conversion operator (returns item name)
		operator const char* ()const;
	};

}

#endif