#ifndef MANAGETASKFILE_H
#define MANAGETASKFILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace jlu {
	class ManageTaskFile {
	   public:
		std::vector<std::string> getContent (const std::string name);
		bool saveDataInFile (const std::vector<std::string>& contentFile, std::string fileName);
		// @todo: get data from done.txt
		// @todo: get info from files (size and datetime of last modification)
	};
}   // namespace jlu
#endif   // MANAGETASKFILE_H
