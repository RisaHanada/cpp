# Overview
This project implements console-based dictionary application that loads a large CSV dictionary file, stores all entries in dynamically allocated memory, and allows users to search for English words and view their definitions. The program also measures the performance of operations using std::chrono and logs events for later review.

This project demonstrates object‑oriented design, dynamic memory management, file parsing, and performance monitoring in modern C++.

### Features
- Load dictionary data from a CSV file (word,pos,definition format)  
- Support for multiple definitions per word  
- Search and display word definitions with optional:  
    - Part-of-speech output  
    - Showing all definitions or only the first one  
- Performance measurement using TimeMonitor  
- Event logging using Logger  
- Fully modular design:  
    - settings  
    - event  
    - logger  
    - timeMonitor  
    - dictionary  
    - main  

### The modules include:  

- **settings** – Manages global configuration.  
- **event** – Stores event name and duration.  
- **logger** – Manages a dynamic array of Event objects.
- **timeMonitor** – Measures execution time of operations.  
- **dictionary** – Stores all dictionary entries in a dynamic array of Word objects. 

## How to Run the Code
```
g++ *.cpp -o dictionary
./dictionary
```