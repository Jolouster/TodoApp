#include "filterTask.h"
#include <iterator>
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

	std::vector<std::string> FilterTask::getClassificationTagsList (
		const std::vector<std::string>& contentFile, const std::string& type) {
		std::vector<std::string> output;
		std::regex pattern;
		std::smatch matchStr;

		if (type == "context") {
			pattern = (R"(\s\@[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		} else if (type == "project") {
			pattern = (R"(\s\+[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		} else if (type == "tag") {
			pattern = (R"(\s\#[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		} else {
			// Devuelve un vector vacío
			return output;
		}

		for (std::string line : contentFile) {
			if (std::regex_search (line, matchStr, pattern)) {
				for (std::string tag : matchStr) {
					if (std::find (output.begin (), output.end (), tag.substr (1)) ==
						output.end ()) {
						output.push_back (tag.substr (1));
					}
				}
			}
		}
		return output;
	}

	std::map<int, std::string> FilterTask::taskByClassification (
		const std::vector<std::string>& contentFile,
		const std::string& classification,
		TaskClassification classType) {
		std::regex pattern;
		std::smatch matchStr;
		std::map<int, std::string> output;
		std::string toMatch = classification;

		if (classType == TaskClassification::tag) {
			pattern = (R"(\s\#[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
			if (classification.rfind ("#", 0) == std::string::npos) {
				toMatch = "#" + classification;
			}
		} else if (classType == TaskClassification::project) {
			pattern = (R"(\s\+[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
			if (classification.rfind ("+", 0) == std::string::npos)
				toMatch = "+" + classification;
		} else if (classType == TaskClassification::context) {
			pattern = (R"(\s\@[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
			if (classification.rfind ("@", 0) == std::string::npos)
				toMatch = "@" + classification;
		}

		int count = 0;

		for (std::string line : contentFile) {
			if (std::regex_search (line, matchStr, pattern)) {
				for (std::string tag : matchStr) {
					if (tag.substr (1) == toMatch) {
						output[count] = line;
					}
				}
			}
			count++;
		}
		return output;
	}
}	// namespace jlu
