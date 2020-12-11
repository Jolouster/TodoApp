#include <iostream>
#include "filterTask.h"
#include "readerFile.h"

namespace jlu {
	void showTodoList (std::vector<std::string>& contentFile) {
		for (std::string& line : contentFile) {
			if (jlu::isTodo (line))
				std::cout << line << std::endl;
		}
	}

	void showDoneList (std::vector<std::string>& contentFile) {
		for (std::string& line : contentFile) {
			if (jlu::isDone (line))
				std::cout << line << std::endl;
		}
	}
}   // namespace jlu

int main (int argc, char* argv[]) {
	std::vector<std::string> contentFile =
		jlu::getContent ("/home/jlopez/Dropbox/ExBrain/todo.txt");

	if (1 < argc) {
		std::string tmp;
		for (int i = 0; i < argc; i++) {
			tmp = argv[i];
			if ("app" == tmp) {
				continue;
			} else if (("-l" == tmp) || ("--list" == tmp)) {
				// list task to do.
				jlu::showTodoList (contentFile);
			} else if (("-la" == tmp) || ("--list-all" == tmp)) {
				// list all task
				for (std::string& line : contentFile) {
					std::cout << line << std::endl;
				}
			} else if (("-a" == tmp) || ("--add" == tmp)) {
				// add new task. Next item must be a text inside of ""
			} else if (("-r" == tmp) || ("--remove" == tmp)) {
				// remove task. Next item must be a index of task
			} else if (("-d" == tmp) || ("--done" == tmp)) {
				// mark as done task. Next item must be a index of task
				jlu::showDoneList (contentFile);
			} else if (("-h" == tmp) || ("--help" == tmp)) {
				// show help
			} else {
				std::cerr << "Argument not valid" << std::endl;
			}
		}
	}
	return EXIT_SUCCESS;
}
