/***********************************************************************
// event Module
// File	event.h
// Date	2026/01/29 
// Author Risa Hanada
// Declares the Event class, which stores information about a 
// single timed operation in the dictionary application.
***********************************************************************/
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <iostream>
#include <string>
#include <chrono>

namespace seneca {
	class Event {
		std::string m_name; // a name describing the operation
		std::chrono::nanoseconds m_duration; // a duration measured in std::chrono::nanoseconds
	public:
        // constructors
		Event();
		Event(const char* name, const std::chrono::nanoseconds& duration);

        // a friend insertion operator (operator<<) used to print formatted event information
		friend std::ostream& operator<<(std::ostream& os, Event& event);
	};
}

#endif