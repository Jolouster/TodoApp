#include "filterTask.h"
#include <regex>

namespace jlu {
	bool FilterTask::isTodo (const std::string& task) {
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

	bool FilterTask::isDone (const std::string& task) {
		bool output = false;
		if (false == task.empty ()) {
			std::regex pattern (R"(^x\s.*)", std::regex::ECMAScript);
			if (std::regex_match (task, pattern)) {
				output = true;
			}
		}
		return output;
	}

	std::map<int, std::string> FilterTask::searchStr (const std::vector<std::string>& contentFile,
										  const std::string patternStr) {
		std::map<int, std::string> output;
		std::regex pattern (patternStr);
		int count = 0;

		for (std::string line : contentFile) {
			if (std::regex_search (line, pattern)) {
				output[count] = line;
			}
			count++;
		}
		return output;
	}

	std::vector<std::string> FilterTask::getTagList (const std::vector<std::string>& contentFile) {}

	std::vector<std::string> FilterTask::getProjectsList (const std::vector<std::string>& contentFile) {}

	std::vector<std::string> FilterTask::getContextList (const std::vector<std::string>& contentFile) {}

	std::map<int, std::string> FilterTask::taskByClassification (const std::vector<std::string>& contentFile,
													 std::string classification,
													 TaskClassification classType) {}
}	// namespace jlu
