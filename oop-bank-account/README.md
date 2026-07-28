# Overview
This project implements a fully functional Account class in C++, modeling a simple bank account with:  

・Account holder name (C-string)  
・Account number (integer)  
・Account balance (double)  

The class supports multiple account states (invalid, new, valid) and demonstrates object‑oriented programming, operator overloading, encapsulation, and safe state management.

### Account States
The class handles three distinct states:

・Invalid State  
Occurs when invalid data is provided.
(number = -1, balance = 0.0, name = "")  
・New State  
Account created but number not yet assigned.
(number = 0, valid name)  
・Valid State  
5‑digit account number, non‑negative balance, non‑empty name.  

## Implemented Components
### Constructors  
`Account(const char holderName)* `  
Creates a new account with zero balance.

`Account(const char holderName, int number, double balance)*`  
Creates a valid account if all values are valid; otherwise sets invalid state.

### Display Function
`ostream& display() const`    
Prints account information depending on its state.

## Implemented Operators
### Type Conversion Operators
`operator bool()` – checks validity

`operator int()` – returns account number

`operator double()` – returns balance

`operator const char*()` – returns holder name

### Subscription Operators
`char& operator[](int index)` – modifiable access

`const char operator[](int index) const` – read‑only access (Out‑of‑range indices wrap around)

### Assignment Operators
`operator=(int)` – sets account number if new

`operator=(double)` – sets balance if non‑negative

### Arithmetic Operators
`operator+=(double)` – deposit

`operator-=(double)` – withdraw (with safety checks)

### Transfer Operators
`operator<<` – move funds from right → left

`operator>>` – move funds from left → right (No action if invalid or same account)

### Unary Operators
`operator~()` – checks if account is new

`operator++()` – add $1

`operator--()` – subtract $1

## How to Run the Code
```
g++ Account.cpp main.cpp -o account
./account
```