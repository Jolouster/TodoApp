#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "filterTask.h"
#include "readerFile.h"

#define APPLICATION_NAME "TodoApp"
#define APPLICATION_VERSION "1.0.0"
#define DATETIME_FORMAT "%F %R"	  // "yyyy-MM-dd HH:mm"
#define TODO_FILE "/home/jlopez/Dropbox/ExBrain/todo.txt"
#define DONE_FILE "/home/jlopez/Dropbox/ExBrain/done.txt"

namespace jlu {
	enum TaskType { todo, done, all };

	std::string actualDateTimeToStr () {
		auto now = std::chrono::system_clock::now ();
		auto in_time_t = std::chrono::system_clock::to_time_t (now);
		std::stringstream ss;
		ss << std::put_time (std::localtime (&in_time_t), DATETIME_FORMAT);
		return ss.str ();
	}

	inline void printLine (const int& count, const std::string& line) {
		std::cout << "    " << count << ".-  " << line << std::endl;
	}

	void printTask (TaskType type, std::vector<std::string> contentFile) {
		int count = 0;
		for (std::string& line : contentFile) {
			if (type == TaskType::todo) {
				if (isTodo (line)) {
					printLine (count, line);
				}
			} else if (type == TaskType::done) {
				if (isDone (line)) {
					printLine (count, line);
				}
			} else if (type == TaskType::all) {
				printLine (count, line);
			}
			count++;
		}
	}

	void showHelp () {
		//@todo: write a good help text
		std::string help;
		help = "How to use this program";
		std::cout << help << std::endl;
	}

	bool saveDataInFile (const std::vector<std::string>& contentFile, std::string fileName) {
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

	void addNewTask (std::vector<std::string>& contentFile, const std::string& newTask) {
		if (newTask.empty ()) {
			//@todo: log error
		} else {
			std::string task (actualDateTimeToStr () + " " + newTask);
			contentFile.push_back (task);

			if (saveDataInFile (contentFile, TODO_FILE)) {
				std::cout << "-----\nNew task added successfully\n\t" << task << std::endl;
			}
		}
	}

	void removeTask (std::vector<std::string>& contentFile, const int idTask) {
		contentFile.erase (contentFile.begin () + idTask);
		if (saveDataInFile (contentFile, TODO_FILE)) {
			std::cout << "-----\nTask " << idTask << " deleted successfully" << std::endl;
		}
	}

	void doneTask (std::vector<std::string>& contentFile, const int idTask) {
		std::string done = "x " + actualDateTimeToStr () + " " + contentFile[idTask];
		contentFile[idTask] = done;
		if (saveDataInFile (contentFile, TODO_FILE)) {
			std::cout << "-----\nTask " << idTask << " marked as done\n\t" << done << std::endl;
		}
	}

	void archiveDoneTasks (std::vector<std::string>& contentFile) {
		std::vector<std::string> auxiliar;
		std::string line;
		for (auto i = contentFile.begin (); i < contentFile.end ();) {
			line = *i;
			if (isDone (line)) {
				auxiliar.push_back (line);
				i = contentFile.erase (i);
			} else {
				i++;
			}
		}

		if (saveDataInFile (auxiliar, DONE_FILE) && saveDataInFile (contentFile, TODO_FILE)) {
			std::cout << "-----\nArchived done tasks in done.txt" << std::endl;
		}
	}
}	// namespace jlu

int main (int argc, char* argv[]) {
	std::vector<std::string> contentFile = jlu::getContent (TODO_FILE);

	if (1 < argc) {
		std::string tmp;
		for (int i = 1; i < argc; i++) {
			tmp = argv[i];
			if (("-l" == tmp) || ("--list" == tmp)) {
				// list task to do.
				if (2 == argc) {
					jlu::printTask (jlu::TaskType::todo, contentFile);
				} else if (3 == argc) {
					//@todo: list only task that cointains the next word
				}
			} else if (("-la" == tmp) || ("--list-all" == tmp)) {
				printTask (jlu::TaskType::all, contentFile);
			} else if (("-ld" == tmp) || ("--list-done" == tmp)) {
				jlu::printTask (jlu::TaskType::done, contentFile);
			} else if (("-a" == tmp) || ("--add" == tmp)) {
				// add new task. Next item must be a text inside of ""
				if ((i + 1) < argc) {
					jlu::addNewTask (contentFile, argv[i + 1]);

					if (3 == argc) {
						break;
					}
				} else {
					std::cout << "After -a argument you must include a task between \"\" Ex: \"Any "
								 "task to do\""
							  << std::endl;
				}
			} else if (("-r" == tmp) || ("--remove" == tmp)) {
				// remove task. Next item must be a index of task
				if (3 <= argc) {
					for (int j = (i + 1); j < argc; j++) {
						std::istringstream iss (argv[j]);
						int index = 0;

						if (iss >> index) {
							jlu::removeTask (contentFile, index);
						} else {
							//@todo log error
							break;
						}
					}
					break;
				}
			} else if (("-d" == tmp) || ("--done" == tmp)) {
				if (3 <= argc) {
					for (int j = (i + 1); j < argc; j++) {
						std::istringstream iss (argv[j]);
						int index = 0;

						if (iss >> index) {
							jlu::doneTask (contentFile, index);
						} else {
							//@todo log error
							break;
						}
					}
					break;
				}
			} else if (("-h" == tmp) || ("--help" == tmp)) {
				jlu::showHelp ();
			} else if (("-v" == tmp) || ("--version" == tmp)) {
				std::cout << APPLICATION_NAME << " - Version: " << APPLICATION_VERSION
						  << " Compiled: " << __DATE__ << " " << __TIME__ << std::endl;
			} else if (("-ar" == tmp) || ("--archive" == tmp)) {
				jlu::archiveDoneTasks (contentFile);
			} else {
				std::cerr << "Argument not valid [" << tmp << "]" << std::endl;
			}
		}
	} else {
		jlu::showHelp ();
	}
	return EXIT_SUCCESS;
}
