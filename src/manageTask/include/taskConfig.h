#ifndef TASKCONFIG_H
#define TASKCONFIG_H

#include <filesystem>
#include <fstream>
#include <regex>
#include <string>

#define CONFIG_FILE "config.ini"

namespace jlu {
	class TaskConfig {
	   public:
		TaskConfig ();
		~TaskConfig ();
		std::string getTodoFileName ();
		std::string getDoneFileName ();

	   private:
		void getConfiguration ();
		void saveDefaultConfiguration ();
		// Variables
		std::string todoFileName;
		std::string doneFileName;
	};
}	// namespace jlu

#endif	 // TASKCONFIG_H
