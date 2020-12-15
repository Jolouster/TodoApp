#include "manageTaskFile.h"

namespace jlu {
	std::vector<std::string> ManageTaskFile::getContent (const std::string fileName) {
		std::vector<std::string> output;

		if (fileName.empty ()) {
			std::cerr << "File name is empty" << std::endl;
		} else {
			std::ifstream file (fileName);

			if (file.is_open ()) {
				std::string line;

				while (std::getline (file, line)) {
					output.push_back (line);
				}
				file.close ();
			} else {
				std::cerr << "Fail to open file" << std::endl;
			}
		}

		return output;
	}

	bool ManageTaskFile::saveDataInFile (const std::vector<std::string>& contentFile, std::string fileName) {
		bool output = false;
		std::ofstream file;

		if (fileName.find ("todo.txt")) {
			file.open (fileName, std::ios_base::trunc);
		} else {
			file.open (fileName, std::ios_base::app);
		}

		if (file.is_open ()) {
			for (std::string tmp : contentFile) {
				file << tmp << "\n";
			}
			output = true;
			file.close ();
		} else {
			std::cerr << "Can't open file: " << fileName << std::endl;
			//@todo: log error
		}

		return output;
	}
}   // namespace jlu
