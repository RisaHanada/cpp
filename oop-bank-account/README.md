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