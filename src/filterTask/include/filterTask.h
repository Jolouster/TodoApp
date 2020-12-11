#ifndef FILTERTASK_H
#define FILTERTASK_H

#include <regex>
#include <string>

namespace jlu {
	bool isTodo (const std::string& task);
	bool isDone (const std::string& task);
}
#endif
