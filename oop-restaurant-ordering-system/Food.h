/***********************************************************************
// Food Module
// File	Food.h
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#pragma once
#ifndef FOOD_H
#define FOOD_H
#include <iostream>
#include "Billable.h"
using namespace std;
namespace seneca {
	class Food : public Billable {
		bool m_ordered; // true if portion selected
		bool m_child; // true if child portion
		char* m_customize; // dynamic customization notes
	public:
        // constructor
		Food();
        // copy constructor
		Food(const Food& food);
        // copy assignment operator
		Food& operator=(const Food& food);
        // destructor
		~Food();
        
        // overrides Billable's order
		std::ostream& print(std::ostream& ostr = cout)const override;
        // overrides Billable's order
		bool order() override;
        // overrides Billable's ordered
		bool ordered()const override;
        // overrides Billable's read
		std::ifstream& read(std::ifstream& file) override;
        // overrides Billable's price 
        // returns adjusted price (child portion = half price)
		double price() const override;
	};
}
#endif