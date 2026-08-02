# Overview
This project implements an application that enables waiters to take customer orders for food and drinks and generate a bill upon order completion. Each bill will have a unique number, and once an order is finalized, the bill will be saved in a separate file named according to its bill number. 

The application is structured into six modules: each responsible for a specific part of the ordering workflow and a main module that launches the program. The project demonstrates object‑oriented programming concepts such as abstraction, inheritance, dynamic memory management, operator overloading, and modular system design.

### The modules include:  

・**Utils** – Provides helper functions for dynamic memory allocation, safe input handling, and common utilities used across the project.  
・**Menu** – Contains MenuItem and Menu classes that manage menu items and allow users to browse and select food or drink options.  
・**Billable** – An abstract base class defining the common interface for all billable items.  
・**Food** – A derived class representing food items, supporting different portion sizes.  
・**Drink** – A derived class representing drink items, supporting different container sizes.  
・**Ordering** – Coordinates the ordering process, manages selected items, calculates totals, and generates bill files.  
・**main** – Launches the application and provides the user interface for waitstaff.

## How to Run the Code
```
g++ *.cpp -o ordering 
./ordering
```