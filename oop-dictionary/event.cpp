/***********************************************************************
// event Module
// File	event.cpp
// Date	2026/01/29 
// Author Risa Hanada
***********************************************************************/
#include "settings.h"
#include "event.h"

namespace seneca {
    /*
    Default constructor
    */
	Event::Event() : m_name{}, m_duration{} {}

    /*
    Initializes name and duration
    */
	Event::Event(const char* name, const std::chrono::nanoseconds& duration) {
		m_name = name;
		m_duration = duration;
	}

    /*
    print formatted event information, including:
    - a persistent call counter
    - right‑aligned event name
    - right‑aligned duration based on g_settings.m_time_units
    */
	std::ostream& operator<<(std::ostream& os, Event& event) {
		static int counter = 1;

		os.setf(std::ios::right);
		os.width(2);
		os << counter << ": ";
		os.width(40);
		os << event.m_name << " -> ";

		using namespace std::chrono;

		if (g_settings.m_time_units == "seconds") {
			auto s = duration_cast<seconds>(event.m_duration);
			os.width(2);
			os << s.count() << " seconds";
		}
		else if (g_settings.m_time_units == "milliseconds") {
			auto ms = duration_cast<milliseconds>(event.m_duration);
			os.width(5);
			os << ms.count() << " milliseconds";
		}
		else if (g_settings.m_time_units == "microseconds") {
			auto us = duration_cast<microseconds>(event.m_duration);
			os.width(8);
			os << us.count() << " microseconds";
		}
		else {
			auto ns = event.m_duration;
			os.width(11);
			os << ns.count() << " nanoseconds";
		}

		counter++;
		return os;
	}
}
