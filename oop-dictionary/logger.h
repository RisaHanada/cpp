/***********************************************************************
// logger Module
// File	logger.h
// Date	2026/01/29 
// Author Risa Hanada
//
// Declares the Logger class, which manages a dynamically allocated array of Event objects. 
// The Logger is responsible for storing all events generated during the execution of the dictionary application.
//
// Key responsibilities:
//   - maintain a dynamic array of Event objects
//   - resize the array when new events are added
//   - support move operations (move constructor and move assignment)
//   - disable copy operations as required by the assignment
//   - provide an insertion operator (operator<<) that prints all
//     stored events, one per line
***********************************************************************/
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include <iostream>
#include "event.h"

namespace seneca {
	class Logger {
		Event* eventArray; // dynamic array of events
		size_t m_num = 0u; // number of stored events
		size_t m_size = 0u; // size of the array
	public:
        // constructor
		Logger();

        // disable copy operations
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

        // destructor
		~Logger();

        // move operations
		Logger(Logger&& src) noexcept;
		Logger& operator=(Logger&& src) noexcept;

        // adds a new Event to the logger, resizing the internal array as needed
		void addEvent(const Event& event);

        // outputs all stored events to the given output stream, one per line
		friend std::ostream& operator<<(std::ostream& os, Logger& logger);
	};
}

#endif
