/***********************************************************************
// Utils Module
// File	Utils.cpp
// Date	2025/11/2
// Author started by Fardad, added getInt() and getInt(int min, int max) by Risa Hanada
***********************************************************************/
#include <iostream>
#include <string>
#include "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {
    Utils ut;

    char* Utils::alocpy(const char* src) const {
        char* des{};
        return alocpy(des, src);
    }

    char* Utils::alocpy(char*& des, const char* src)const {
        delete[] des;
        des = nullptr;
        if (src) {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
        return des;
    }
    char* Utils::strcpy(char* des, const char* src)const {
        int i;
        for (i = 0; src[i]; i++) des[i] = src[i];
        des[i] = char(0);
        return des;
    }
    int Utils::strlen(const char* str)const {
        int len;
        for (len = 0; str[len]; len++);
        return len;
    }

    bool Utils::isspace(char ch)const {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    bool Utils::isspace(const char* cstring) const {
        while (cstring && isspace(*cstring)) {
            cstring++;
        }
        return cstring && *cstring == 0;
    }
   
    /*
    Repeatedly prompts the user until a properly formatted integer is entered. 
    Handles empty input, non‑numeric input, and trailing characters, ensuring that only a clean, valid integer is accepted. 
    The input buffer is cleared after each attempt to prepare for future entries.
    */
    int getInt() {
        char input[MaximumNumberOfMenuItems];
        int value = 0;
        bool valid = false;

        while (!valid) {

            cin.getline(input, MaximumNumberOfMenuItems);
            int len = ut.strlen(input);

            bool empty = true;
            for (int i = 0; i < len; i++) {
                if (!ut.isspace(input[i])) {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                cout << "You must enter a value: ";
                continue;
            }

            int i = 0;
            bool integer = false;
            if (input[i] == '-') {
                integer = true;
                i++;
            }

            if (!isdigit(input[i])) {
                cout << "Invalid integer: ";
                continue;
            }

            int num = 0;
            while (i < len && isdigit(input[i])) {
                int digit = input[i] - '0';
                num = num * 10;
                num = num + digit;
                i++;
            }

            bool followingChar = false;
            while (i < len) {
                if (!ut.isspace(input[i])) {
                    followingChar = true;
                }
                i++;
            }
            if (followingChar) {
                cout << "Only an integer please: ";
                continue;
            }

            if (integer) {
                value = -num;
            }
            else {
                value = num;
            }
            valid = true;
        }

        return value;
    }
    
    /*
    Retrieves a validated integer within the inclusive range [min, max].
    Uses getInt() for basic integer validation and adds range checking.
    */
    int getInt(int min, int max) {
        int value = getInt();
        while(!(value >= min && value <= max)){
            cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
            value = getInt();
        }
        return value;
    }

    char* Utils::makeBillFileName(char* filename, size_t billNo)const {
        char billFileName[21] = "bill_";
        size_t temp = billNo;
        int cnt = 5;
        int length;
        // Calculate the number of digits
        do {
            cnt++;
            temp /= 10;
        } while (temp > 0);
        length = cnt;
        // Convert each digit to character from the end
        while (billNo > 0) {
            billFileName[--cnt] = (billNo % 10) + '0';
            billNo /= 10;
        }
        // Handle the case when billNo is 0
        if (billFileName[cnt - 1] == '\0') {
            billFileName[--cnt] = '0';
        }
        // Attach .txt to the end of the file name
        for (int i = 0; ".txt"[i]; i++) {
            billFileName[length++] = ".txt"[i];
        }
        billFileName[length] = '\0';
        strcpy(filename, billFileName);
        return filename;
    }
}