/***********************************************************************
// OOP244 Workshop 4 lab: Account Module
//
// File	Account.h
// Author Risa Hanada
***********************************************************************/
#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca {
    const int NameMaxLen = 30;
    class Account {
        double m_balance;
        int m_number;
        char m_holderName[NameMaxLen + 1];
        void cpyName(const char* src); // copies the src into the m_holderName array
        bool isValidNumber(int number)const; // returns true if number is a valid account number
    public:
        // constructors
        Account(const char* holderName = nullptr); 
        Account(const char* holderName, int number, double balance);

        // display function
        std::ostream& display()const;

        // type conversion member operators
        operator bool() const;
        operator int() const;
        operator double() const;
        operator const char* () const;

        // subscription operators
        char& operator[](int index);
        const char operator[](int index) const;

        // binary member operators
        Account& operator=(int num);
        Account& operator=(double balance);
        Account& operator+=(double deposit);
        Account& operator-=(double withdraw);
        Account& operator<<(Account& right);
        Account& operator>>(Account& right);

        // unary member operators
        bool operator~() const;
        Account& operator++();
        Account operator++(int);
        Account& operator--();
        Account operator--(int);
    };


}
#endif // SENECA_ACCOUNT_H_