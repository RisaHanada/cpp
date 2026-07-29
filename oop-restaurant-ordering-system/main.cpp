/***********************************************************************
// File	main.cpp
// Date	2025/11/20 
// Author Fardad
***********************************************************************/
#include "Menu.h"
#include "Ordering.h"
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include <iostream>
using namespace std;
using namespace seneca;

    int main() {
        Ordering ord("drinks.csv", "foods.csv");
        if (!ord) {
            cout << "Failed to open data files or the data files are corrupted!" << endl;
            return 0;
        }
        Drink D1, D2;
        ifstream file("drinks.csv");
        ofstream fileout("drinkout.csv");

        Menu menu1("Seneca Restaurant ", "End Program");
        menu1 << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
        Menu menu2("Order Menu", "Back to main menu", 1);
        menu2 << "Food" << "Drink";
        Menu menu3("You have bills that are not saved, are you sue you want to exit?", "No");
        menu3 << "Yes";

        size_t selection{};
        size_t orderSelection{};       
        do {
            switch (selection = menu1.select()) {
            case 1:
                do {
                    switch (orderSelection = menu2.select())
                    {
                    case 1:
                        ord.orderFood();
                        break;
                    case 2:
                        ord.orderDrink();
                        break;
                    }
                } while (orderSelection);
                break;
            case 2:
                ord.printBill(cout);
                break;
            case 3:
                ord.resetBill();
                break;
            case 4:
                ord.listFoods();
                break;
            case 5:
                ord.listDrinks();
                break;
            case 0:
                if (ord.hasUnsavedBill()) {
                    if (menu3.select() == 1) {
                        return 0;
                    }
                    else {
                        selection = -1;
                        break;
                    }
                }
                else {
                    return 0;
                }

            }
        } while (selection);
        cout << "End **********************************************" << endl;


        return 0;
    }