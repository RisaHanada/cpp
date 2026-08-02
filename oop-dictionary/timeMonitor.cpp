/***********************************************************************
// timeMonitor Module
// File	timeMonitor.cpp
// Date	2026/01/29 
// Author Risa Hanada
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "timeMonitor.h"
#include <cstring>

namespace seneca {
    /*
    Records the event name and the time at which the event starts.
    */
	void TimeMonitor::startEvent(const char* name) {
		strcpy(eventName, name);
		m_start = std::chrono::steady_clock::now();
	}

    /*
    Stops timing, calculates the duration, and returns an Event object.
    */
	Event TimeMonitor::stopEvent() {
		auto m_end = std::chrono::steady_clock::now();
		auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start);
		return Event(eventName, time);
	}
}