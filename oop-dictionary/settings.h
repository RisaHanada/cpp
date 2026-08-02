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
		bool m_show_all = false;
		bool m_verbose = false;
		std::string m_time_units = "nanoseconds";
	};
	extern Settings g_settings;
}

#endif