/***********************************************************************
// Ordering Module
// File	Ordering.cpp
// Date	2025/11/20 
// Author Risa Hanada
***********************************************************************/
#include "Ordering.h"
#include "constants.h"
#include "Food.h"
#include "Drink.h"
#include "Menu.h"
#include "Utils.h"
#include <iostream>

using namespace std;
namespace seneca {
    /*
    Prints the bill header using the current bill number.
    Used at the beginning of every printed or saved bill.
    */
	void Ordering::billTitlePrint(std::ostream& os) const {
		os << "Bill # ";
		os.width(3);
		os.fill('0');
		os << billSerialNum << " =============================" << endl;
	}

    /*
    Prints the bill footer including:
    - Total
    - Tax (using Tax constant)
    - Total + Tax
    */
	void Ordering::printTotal(std::ostream& os, double total) const {
		os.setf(ios::fixed);
		os.setf(ios::right);

		os.width(31);
		os.fill(' ');
		os << "Total:    ";

		os.width(9);
		os.fill(' ');
		os.precision(2);
		os << total << endl;

		os.width(31);
		os.fill(' ');
		os << "Tax:      ";

		double t = total * Tax;
		os.width(9);
		os.fill(' ');
		os.precision(2);
		os << t << endl;

		os.width(31);
		os.fill(' ');
		os << "Total+Tax:";

		double tt = total + t;
		os.width(9);
		os.fill(' ');
		os.precision(2);
		os << tt << endl;

		os << "========================================" << endl;
	}

    /*
    Counts newline characters in the given file to determine how many records it contains.
    Used to size dynamic arrays for foods and drinks.
    */
	size_t Ordering::countRecords(const char* file) const {
		size_t newLine = 0;
		char x;
		ifstream f;
		f.open(file);
		if (f.is_open()) {
			while (f.get(x)) {
				if (x == '\n') {
					newLine++;
				}
			}
		}
		return newLine;
	}

    /*
    Loads drink and food data from files, allocates dynamic arrays, and initializes counters.
    If loading fails, arrays are deleted and set to nullptr.
    */
	Ordering::Ordering(const char* drinksFile, const char* foodsFile) {
		foodArr = nullptr;
		drinkArr = nullptr;
		for (size_t i = 0; i < MaximumNumberOfBillItems; ++i) {
			BillItem[i] = nullptr;
		}
		food = 0;
		drink = 0;
		billable = 0;
		billSerialNum = 1;

		size_t drinkCount = countRecords(drinksFile);
		size_t foodCount = countRecords(foodsFile);

		ifstream drinkFile(drinksFile);
		ifstream foodFile(foodsFile);

		foodArr = new Food[foodCount];
		drinkArr = new Drink[drinkCount];

		unsigned int readDrink = 0;
		unsigned int readFood = 0;
		if (drinkFile && foodFile) {
			for (size_t i = 0; i < drinkCount && drinkFile; i++) {
				if (drinkArr[i].read(drinkFile)) {
					readDrink++;
				}
			}
			for (size_t i = 0; i < foodCount && foodFile; i++) {
				if (foodArr[i].read(foodFile)) {
					readFood++;
				}
			}
		}
		else {
			delete[] drinkArr;
			delete[] foodArr;
			foodArr = nullptr;
			drinkArr = nullptr;
		}

		if (readDrink != drinkCount || readFood != foodCount) {
			delete[] drinkArr;
			delete[] foodArr;
			drinkArr = nullptr;
			foodArr = nullptr;
		}
		else {
			drink = readDrink;
			food = readFood;
		}

	}

    /*
    Releases dynamic arrays for foods and drinks.
    Releases all dynamically created bill items stored in the Billable pointer array.
    */
	Ordering::~Ordering() {
		delete[] foodArr;
		delete[] drinkArr;

		for (size_t i = 0; i < MaximumNumberOfBillItems; ++i) {
			delete BillItem[i];
			BillItem[i] = nullptr;
		}
		billable = 0;
		foodArr = nullptr;
		drinkArr = nullptr;
	}

    /*
    Returns true if both food and drink arrays were successfully loaded.
    */
	Ordering::operator bool() const {
		return foodArr != nullptr && drinkArr != nullptr;
	}

    /*
    Returns the number of billable items currently in the bill.
    */
	size_t Ordering::noOfBillItems() const {
		return (size_t)billable;
	}

    /*
    Returns true if the bill contains at least one item.
    */
	bool Ordering::hasUnsavedBill() const {
		return billable > 0;
	}

    /*
    Prints a header, all food items using their print method, and a footer.
    */
	void Ordering::listFoods() const {
		cout << "List Of Avaiable Meals" << endl;
		cout << "========================================" << endl;
		for (size_t i = 0; i < food; i++) {
			foodArr[i].print() << endl;
		}
		cout << "========================================" << endl;
	}

    /*
    Prints a header, all drink items using their print method, and a footer.
    */
	void Ordering::listDrinks() const {
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================" << endl;
		for (size_t i = 0; i < drink; i++) {
			drinkArr[i].print() << endl;
		}
		cout << "========================================" << endl;
	}

    /*
    Creates a “Food Menu” using the Menu class.
    Allows the waiter to select a food item.
    If selected:
    - Dynamically copies the food item
    - Calls its order() method
    - Adds it to the bill if ordered
    If not ordered, the temporary item is deleted.
    */
	void Ordering::orderFood() {
		Menu menu("Food Menu", "Back to Order", 2);
		for (unsigned int i = 0; i < food && i < MaximumNumberOfMenuItems; i++) {
			menu << (const char*)foodArr[i];
		}
		size_t select = menu.select();
		if (select != 0) {
			Food* f = new Food(foodArr[select - 1]);
			Billable* b = f;
			if (b->order()) {
				BillItem[billable] = b;
				billable++;
			}
			else {
				delete f;
			}

		}

	}

    /*
    Creates a “Drink Menu” using the Menu class.
    Allows the waiter to select a drink item.
    If selected:
    - Dynamically copies the drink item
    - Calls its order() method
    - Adds it to the bill if ordered
    If not ordered, the temporary item is deleted.
    */
	void Ordering::orderDrink() {
		Menu menu("Drink Menu", "Back to Order", 2);
		for (size_t i = 0; i < drink && i < MaximumNumberOfMenuItems; i++) {
			menu << (const char*)drinkArr[i];
		}
		size_t select = menu.select();
		if (select != 0) {
			Drink* d = new Drink(drinkArr[select - 1]);
			Billable* b = d;
			if (b->order()) {
				BillItem[billable] = b;
				billable++;
			}
			else {
				delete d;
			}

		}
	}

    /*
    Prints:
    - Bill header
    - Each bill item
    - Total, tax, and grand total
    */
	void Ordering::printBill(std::ostream& os) const {
		double total = 0.0;
		billTitlePrint(os);
		for (size_t i = 0; i < billable; i++) {
			if (BillItem[i]) {
				BillItem[i]->print(os);
				os << endl;
				total += BillItem[i]->price();

			}
		}
		printTotal(os, total);
	}

    /*
    Saves the current bill to a uniquely named file using the bill number.
    Prints confirmation messages.
    Deletes all bill items.
    Increments bill number.
    Resets bill counter to zero.
    */
	void Ordering::resetBill() {
		char file[20];
		ut.makeBillFileName(file, billSerialNum);
		ofstream f;
		f.open(file);
		if (f) {
			printBill(f);
			f.close();
		}
		cout << "Saved bill number " << billSerialNum << endl;
		cout << "Starting bill number " << billSerialNum + 1 << endl;

		for (size_t i = 0; i < billable; ++i) {
			delete BillItem[i];
			BillItem[i] = nullptr;
		}
		billSerialNum++;
		billable = 0;
	}
}