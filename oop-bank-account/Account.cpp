/***********************************************************************
// OOP244 Workshop 4 lab: Account Module
//
// File	Account.cpp
// Date	2025/06/03
// Author Risa Hanada
***********************************************************************/
#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca {

    /*
    Copies the content of the src C‑string into the m_holderName array.
    */
    void Account::cpyName(const char* src) {
        int i;
        for (i = 0; src && src[i] && i < NameMaxLen; i++) {
            m_holderName[i] = src[i];
        }
        m_holderName[i] = char(0);
    }

    /*
    Checks whether the given integer is a valid account number.
    Returns true only if the number meets the required format for a proper account number.
    */
    bool Account::isValidNumber(int number) const {
        return number >= 10000 && number <= 99999;
    }

    /*
    Sets the account as new, with a balance of 0.0.
    */
    Account::Account(const char* holderName) {
        m_holderName[0] = char(0);
        m_number = -1;
        m_balance = 0.0;
        if (holderName && holderName[0]) {
            cpyName(holderName);
            m_number = 0;
        }
    }

    /*
    Sets the account holder’s name, the account number, 
    and the balance to the provided values, but only if all values are valid. 
    If an invalid or empty C-string is provided, or if an invalid account number 
    or a negative balance is passed to the constructor, the object is set to the invalid empty state.
    */
    Account::Account(const char* holderName, int number, double balance) {
        m_holderName[0] = char(0);
        m_number = -1;
        m_balance = 0.0;
        if (holderName && holderName[0] && isValidNumber(number)
            && balance > 0) {
            cpyName(holderName);
            m_number = number;
            m_balance = balance;
        }
    }

    /*
    Displays the account information on the screen.
    If the account is invalid, it prints Bad Account.
    If the account is new, it prints New instead of the account number.
    The function returns the cout object to allow chaining.
    */
    std::ostream& Account::display() const {
        if (*this) {
            cout << " ";
            cout.fill(' ');
            cout.width(NameMaxLen);
            cout.setf(ios::left);
            cout << m_holderName;
            cout.unsetf(ios::left);
            cout << " | ";
            cout << m_number;
            cout << " | ";
            cout.width(12);
            cout.precision(2);
            cout.setf(ios::right);
            cout.setf(ios::fixed);
            cout << m_balance;
            cout.unsetf(ios::right);
            cout << " ";
        }
        else if (~*this) {
            cout << " ";
            cout.fill(' ');
            cout.width(30);
            cout.setf(ios::left);
            cout << m_holderName;
            cout.unsetf(ios::left);
            cout << " |  NEW  |         0.00 ";
        }
        else {
            cout << " Bad Account                    | ----- | ------------ ";
        }
        return cout;
    }

    /*
    Returns true if the account is valid; otherwise, returns false. This operator does not modify the Account object.
    */
    Account::operator bool() const {
        bool t = m_number != -1 && m_number >= 10000 && m_number <= 99999 && m_balance >= 0 && m_holderName[0] != '\0';
        return t;
    }

    /*
    Returns the account number. This operator does not modify the Account object.
    */
    Account::operator int() const {
        return m_number;
    }

    /*
    Returns the balance value. This operator does not modify the Account object.
    */
    Account::operator double() const {
        return m_balance;
    }

    /*
    Returns the address of the account holder’s name. This operator does not modify the Account object.
    */
    Account::operator const char* () const {
        return m_holderName;
    }

    /*
    Returns a reference to the character at the specified index in the account holder’s name. 
    This operator allows modification of the character at that position. 
    If the index is out of bounds, it should safely handle the request by looping back (e.g., A[30] should behave the same as A[0]).
    */
    char& Account::operator[](int index) {
        index = index % NameMaxLen;
        return m_holderName[index];
    }

    /*
    Returns a copy of the character at the specified index in the account holder’s name. 
    This operator does not allow modification of the character. 
    If the index is out of bounds, it should safely handle the request by looping back (e.g., A[30] should behave the same as A[0]).
    */
    const char Account::operator[](int index) const {
        if (index > (NameMaxLen + 1)) {
            for (int i = 0; index <= (NameMaxLen - 1); i++) {
                index = index - (NameMaxLen - 1);
            }
        }
        char copy = m_holderName[index];
        return copy;
    }

    /*
    Sets the account number to the given integer only if the account is new and the number is valid.
    If the number is invalid, the account is set to the invalid empty state.
    */
    Account& Account::operator=(int num) {
        if (m_number == 0) {
            if (isValidNumber(num)) {
                m_number = num;
            }
            else {
                m_number = -1;
                m_balance = 0.0;
                m_holderName[0] = '\0';
            }
        }
        return *this;
    }

    /*
    Sets the account balance to the given value if it is non‑negative.
    */
    Account& Account::operator=(double balance) {
        if (balance >= 0) {
            m_balance = balance;
        }
        else {
            m_balance = 0.0;
        }
        return *this;
    }

    /*
    Adds the given amount to the account balance (deposit).
    No action is taken if the account is invalid or the amount is negative.
    */
    Account& Account::operator+=(double deposit) {
        if (*this) {
            if(deposit >= 0)
                m_balance += deposit;
        }
        return *this;
    }

    /*
    Subtracts the given amount from the account balance (withdrawal).
    No action is taken if the account is invalid, the amount is negative, or the balance is insufficient.
    */
    Account& Account::operator-=(double withdraw) {
        if (*this) {
            if (withdraw >= 0 && m_balance >= withdraw)
                m_balance -= withdraw;
        }
        return *this;
    }

    /*
    Transfers all funds from the right account into the left account.
    The left account’s balance becomes the sum of both balances, and the right account’s balance becomes zero.
    */
    Account& Account::operator<<(Account& right) {
        if (*this && right) {
            if (this != &right) {
                m_balance += right.m_balance;
                right.m_balance = 0;
            }
        }
        return *this;
    }

    /*
    Transfers all funds from the left account into the right account.
    The right account’s balance becomes the sum of both balances, and the left account’s balance becomes zero.
    */
    Account& Account::operator>>(Account& right) {
        if (*this && right) {
            if (this != &right) {
                right.m_balance += m_balance;
                m_balance = 0;
            }
        }
        return *this;
    }

    /*
    Returns true if the account is new (account number is zero).
    */
    bool Account::operator~() const {
        return m_number == 0;
    }

    /*
    Prefix increment.
    Adds one dollar to the balance and returns a reference to the updated account.
    */
    Account& Account::operator++() {
        m_balance+=1;
        return *this;
    }

    /*
    Postfix increment.
    Adds one dollar to the balance but returns a copy of the account before the increment.
    */
    Account Account::operator++(int) {
        Account copy = *this;
        ++(*this);
        return copy;
    }

    /*
    Prefix decrement.
    Subtracts one dollar from the balance and returns a reference to the updated account.
    */
    Account& Account::operator--() {
        m_balance -= 1;
        return *this;
    }

    /*
    Postfix decrement.
    Subtracts one dollar from the balance but returns a copy of the account before the decrement.
    */
    Account Account::operator--(int) {
        Account copy = *this;
        --(*this);
        return copy;
    }

}