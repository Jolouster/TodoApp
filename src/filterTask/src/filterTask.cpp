#include "filterTask.h"
#include <regex>

namespace jlu {
	bool isTodo (const std::string& task) {
		bool output = true;
		if (task.empty ()) {
			output = false;
		} else {
			std::regex pattern (R"(^x\s.*)", std::regex::ECMAScript);
			if (std::regex_match (task, pattern)) {
				output = false;
			}
		}
		return output;
	}

	bool isDone (const std::string& task) {
		bool output = false;
		if (false == task.empty ()) {
			std::regex pattern (R"(^x\s.*)", std::regex::ECMAScript);
			if (std::regex_match (task, pattern)) {
				output = true;
			}
		}
		return output;
	}
}   // namespace jlu
