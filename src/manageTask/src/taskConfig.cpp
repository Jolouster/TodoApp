#include "taskConfig.h"

namespace jlu {
	TaskConfig::TaskConfig () { getConfiguration (); }

	TaskConfig::~TaskConfig () {
		// destructor
	}

	std::string TaskConfig::getTodoFileName () { return todoFileName; }

	std::string TaskConfig::getDoneFileName () { return doneFileName; }

	// Metodos privados

	void TaskConfig::getConfiguration () {
		std::string contentFile;
		std::ifstream file (CONFIG_FILE, std::ios_base::in);

		if (file.is_open ()) {
			std::string line;
			std::regex patterTodoPath (R"(^path_todo_file=(.*))", std::regex::ECMAScript);
			std::regex patterDonePath (R"(^path_done_file=(.*))", std::regex::ECMAScript);

			while (std::getline (file, line)) {
				if (std::regex_match (line, patterTodoPath)) {
					todoFileName = line.substr (15);
				} else if (std::regex_match (line, patterDonePath)) {
					doneFileName = line.substr (15);
				}
			}
			file.close ();
		} else {
			saveDefaultConfiguration ();
		}
	}

	void TaskConfig::saveDefaultConfiguration () {
		std::string contentDefault =
			"path_todo_file=~/Dropbox/todo.txt\npath_done_file=~/Dropbox/done.txt";
		std::ofstream file (CONFIG_FILE, std::ios_base::out);

		if (file.is_open ()) {
			file << contentDefault;
		}
		file.close ();
	}
}	// namespace jlu
