/***********************************************************************
// logger Module
// File	logger.cpp
// Date	2026/01/29 
// Author Risa Hanada
***********************************************************************/
#include "logger.h"

namespace seneca {
    /*
    Initializes eventArray, m_num and m_size.
    */
	Logger::Logger() {
		eventArray = nullptr;
		m_num = 0;
		m_size = 0;
	}

    /*
    Releases dynamically allocated memory used for eventArray.
    */
	Logger::~Logger() {
		delete[] eventArray;
		eventArray = nullptr;
	}

    /*
    Move constructor: Transfers ownership of the event array from another logger.
    */
	Logger::Logger(Logger&& src) noexcept {
		*this = std::move(src);
	}

    /*
    Move assignment operator: cleans up current resources and takes ownership from another logger.
    */
	Logger& Logger::operator=(Logger&& src) noexcept {
		if (this != &src) {
			delete[] eventArray;
			m_num = src.m_num;
			m_size = src.m_size;
			eventArray = src.eventArray;
			src.eventArray = nullptr;
			src.m_num = 0;
			src.m_size = 0;
		}
		return *this;
	}

    /*
    Adds a new event to the logger, resizing the internal array to store it.
    */
	void Logger::addEvent(const Event& event) {
		if (m_size == m_num) {
			unsigned addSize = ++m_size;
			Event* temp = new Event[addSize];
			for (size_t i = 0; i < m_num; i++) {
				temp[i] = eventArray[i];
			}
			delete[] eventArray;
			eventArray = temp;
			m_size = addSize;
		}
		eventArray[m_num] = event;
		m_num++;
	}

    /*
    Prints all stored events to the output stream, one per line.
    */
	std::ostream& operator<<(std::ostream& os, Logger& logger) {
		for (size_t i = 0; i < logger.m_num; i++) {
			os << logger.eventArray[i] << std::endl;
		}
		return os;
	}
}