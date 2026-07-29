/***********************************************************************
// Drink Module
// File	Drink.h
// Date	2025/11/9 
// Author Risa Hanada
***********************************************************************/
#pragma once
#ifndef DRINK_H
#define DRINK_H
#include <iostream>
#include "Billable.h"
using namespace std;
namespace seneca {
	class Drink :  public Billable{
		char m_size; // S, M, L, X or unset
	public:
        // overrides Billable's print
		std::ostream& print(std::ostream& ostr = cout)const override;
        // overrides Billable's order
		bool order() override;
        // overrides Billable's ordered
		bool ordered()const override;
        // overrides Billable's read
		std::ifstream& read(std::ifstream& file) override;
        // overrides Billable's price
		double price() const override;
	};
}
#endif