/***********************************************************************
// settings Module
// File	settings.h
// Date	2026/01/29 
// Author Risa Hanada
***********************************************************************/
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>

namespace seneca {
	struct Settings {
		bool m_show_all = false; // when true, if a word has multiple definitions, all definitions should be printed on screen, otherwise only the first definition should be shown (default false).
		bool m_verbose = false; // when true, print to screen the part-of-speech of a word if it exists (default false).
		std::string m_time_units = "nanoseconds"; // stores the time units to be used when printing duration of various operations (default nanoseconds). 
	};
	extern Settings g_settings; // all configuration options are stored in a global instance (g_settings)
}

#endif