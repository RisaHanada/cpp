/***********************************************************************
// Ordering Module
// File	Ordering.h
// Date	2025/11/20 
// Author Risa Hanada
***********************************************************************/
#pragma once
#ifndef ORDERING_H
#define ORDERING_H
#include "Drink.h"
#include "Food.h"
#include "constants.h"
#include <iostream>
namespace seneca {
	class Ordering {
		unsigned int food; // number of food items loaded from file
		unsigned int drink; // number of drink items loaded from file
		unsigned int billable; // number of billable items currently in the bill
		unsigned int billSerialNum; // serial bill number (increments after each saved bill)

		Food* foodArr; // dynamic arrays of available food items
		Drink* drinkArr; // dynamic arrays of available drink items
		Billable* BillItem[MaximumNumberOfBillItems]; // array of pointers to dynamically created bill items

		void billTitlePrint(std::ostream& os = std::cout) const; // prints bill header
		void printTotal(std::ostream& os, double total) const; // prints totals, tax, and grand total
		size_t countRecords(const char* file) const; // counts number of newline-separated records in a file
	public:
        // constructor
		Ordering(const char* drinksFile, const char* foodsFile);
        // destructor
		~Ordering();
        // bool conversion
		operator bool() const;
        // returns number of items currently in the bill
		size_t noOfBillItems() const;
        // returns true if the bill contains unsaved items
		bool hasUnsavedBill() const;
        // prints all available food items
		void listFoods() const;
        // prints all available drink items
		void listDrinks() const;
        // takes a food order using a Menu object
		void orderFood();
        // takes a drink order using a Menu object
		void orderDrink();
        // prints the current bill to the given ostream
		void printBill(std::ostream& os) const;
        // saves the current bill to a file, resets bill items, increments bill number, and prepares for next bill
		void resetBill();
	};
}
#endif
