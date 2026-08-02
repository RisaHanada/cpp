/***********************************************************************
// timeMonitor Module
// File	timeMonitor.h
// Date	2026/01/29 
// Author Risa Hanada
//
// Declares the TimeMonitor class, which measures the duration
// of operations in the dictionary application using std::chrono.
//
// Responsibilities:
//   - record the start time of an event
//   - record the end time and compute the duration
//   - return an Event object containing the event name and duration
***********************************************************************/
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <chrono>
#include "event.h"

namespace seneca {
	class TimeMonitor {
		std::chrono::steady_clock::time_point m_start; // start time of the event
		char eventName[100]; // name of the current event
	public:
        // records the event name and the time at which the event begins
		void startEvent(const char* name);

        // stops timing, computes the duration, and returns an Event object
		Event stopEvent();
	};
}

#endif
