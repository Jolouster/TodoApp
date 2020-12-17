#ifndef FILTERTASK_H
#define FILTERTASK_H

#include <map>
#include <regex>
#include <string>
#include <vector>

namespace jlu {
	class FilterTask {
	   public:
		enum TaskClassification { tag, project, context };
		bool isTodo (const std::string& task);
		bool isDone (const std::string& task);
		std::map<int, std::string> searchStr (const std::vector<std::string>& contentFile,
											  const std::string patternStr);
		std::vector<std::string> getTagList (const std::vector<std::string>& contentFile);
		std::vector<std::string> getProjectsList (const std::vector<std::string>& contentFile);
		std::vector<std::string> getContextList (const std::vector<std::string>& contentFile);
		std::vector<std::string> getClassificationTagsList (
			const std::vector<std::string>& contentFile, const std::string& type);
		std::map<int, std::string> taskByClassification (
			const std::vector<std::string>& contentFile,
			const std::string& classification,
			TaskClassification classType);

	   private:
	};
}	// namespace jlu
#endif
