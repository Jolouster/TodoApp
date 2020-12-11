#include "readerFile.h"

namespace jlu {
	std::vector<std::string> getContent (const std::string fileName) {
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
}   // namespace jlu
