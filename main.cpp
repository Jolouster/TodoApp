#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "filterTask.h"
#include "readerFile.h"

#define APPLICATION_NAME "TodoApp"
#define APPLICATION_VERSION "1.0.0"
#define DATETIME_FORMAT "%F %R"	  // "yyyy-MM-dd HH:mm"
#define TODO_FILE "/home/jlopez/Dropbox/ExBrain/todo.txt"
#define DONE_FILE "/home/jlopez/Dropbox/ExBrain/done.txt"

// Color codes
#define BLACK "\033[0m"
#define GRAY "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RGREEN "\033[32m"
#define YELOW "\033[1;33m"
#define RYELOW "\033[33m"
#define BLUE "\033[1;34m"
#define VIOLET "\033[1;35m"
#define CYAN "\033[1;36m"
#define LGRAY "\033[1;37m"

namespace jlu {
	enum TaskType { todo, done, all };

	std::string actualDateTimeToStr () {
		auto now = std::chrono::system_clock::now ();
		auto in_time_t = std::chrono::system_clock::to_time_t (now);
		std::stringstream ss;
		ss << std::put_time (std::localtime (&in_time_t), DATETIME_FORMAT);
		return ss.str ();
	}

	void printLine (const int& count, const std::string& line) {
		const std::regex pattern (R"(^\d\d\d\d-\d\d-\d\d \d\d:\d\d)");
		if (std::regex_search (line, pattern)) {
			std::string dateTime = line.substr (0, 16);
			std::string taskDescription = line.substr (16);
			std::cout << "    " << count << ".-  " << RYELOW << dateTime << BLACK << taskDescription
					  << std::endl;
		} else {
			std::cout << "    " << count << ".-  " << line << std::endl;
		}
	}

	void printLine (const int& count, const std::string& line, std::string color) {
		std::regex patternWithDate (R"(^\d\d\d\d-\d\d-\d\d \d\d:\d\d)");
		std::regex patDoneWithDates (
			R"(^x \d\d\d\d-\d\d-\d\d \d\d:\d\d \d\d\d\d-\d\d-\d\d \d\d:\d\d)");
		if (std::regex_search (line, patternWithDate)) {
			std::string dateTime = line.substr (0, 16);
			std::string taskDescription = line.substr (16);
			std::cout << "    " << count << ".-  " << RYELOW << dateTime << color << taskDescription
					  << BLACK << std::endl;
		} else if (std::regex_search (line, patDoneWithDates)) {
			std::string xStr = line.substr (0, 2);	 // include a space
			std::string endDateTime = line.substr (2, 16);
			std::string startDateTime = line.substr (18, 17);	// include a space
			std::string taskDesc = line.substr (35);
			std::cout << "    " << count << ".-  ";
			std::cout << GREEN << xStr << BLACK;
			std::cout << RGREEN << endDateTime << RYELOW << startDateTime;
			std::cout << color << taskDesc << BLACK << std::endl;
		} else {
			std::cout << "    " << count << ".-  " << color << line << BLACK << std::endl;
		}
	}

	void printTask (TaskType type, std::vector<std::string> contentFile) {
		int count = 0, todos = 0, dones = 0;
		std::cout << "     ID     DESCRIPTION\n";
		std::cout << "    ----------------------------------------------" << std::endl;

		if (contentFile.empty ()) {
			std::cout << "    The task list is empty" << std::endl;
		} else {
			for (std::string& line : contentFile) {
				if (type == TaskType::todo) {
					if (isTodo (line)) {
						printLine (count, line);
						todos++;
					} else {
						dones++;
					}
				} else if (type == TaskType::done) {
					if (isDone (line)) {
						printLine (count, line, GRAY);
						dones++;
					} else {
						todos++;
					}
				} else if (type == TaskType::all) {
					if (isTodo (line)) {
						printLine (count, line);
						todos++;
					} else {
						printLine (count, line, GRAY);
						dones++;
					}
				}
				count++;
			}
		}
		std::cout << "\n    -----------\n    TO-DO: " << VIOLET << todos << BLACK
				  << " DONE: " << GREEN << dones << BLACK << " TOTAL: " << BLUE << (todos + dones)
				  << BLACK << " - " << CYAN << ((dones * 100) / (todos + dones)) << "% " << BLACK
				  << "DONE!" << std::endl;
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

	void changeTask (std::vector<std::string>& contentFile, const int idTask) {
		//@todo: remove creation date from string
		std::cout << "Old [ID:" << idTask << "] = \"" << contentFile[idTask] << "\"" << std::endl;
		std::cout << "New: ";
		std::string newTask;
		std::getline (std::cin, newTask);
		contentFile[idTask] = actualDateTimeToStr () + " " + newTask;

		if (saveDataInFile (contentFile, TODO_FILE)) {
			std::cout << "-----\nTask changed successfully" << std::endl;
		}
	}

	void searchTask (std::vector<std::string>& contentFile, const std::string& pattern) {
		std::vector<std::string> auxiliar;
		std::regex reg (pattern);
		int count = 0;

		std::cout << "     ID     DESCRIPTION\n";
		std::cout << "    ----------------------------------------------" << std::endl;

		for (std::string line : contentFile) {
			if (std::regex_search (line, reg)) {
				if (isDone (line)) {
					printLine (count, line, GRAY);
				} else {
					printLine (count, line);
				}
			}
			count++;
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
					jlu::searchTask (contentFile, argv[i + 1]);
					break;
				}
			} else if (("-la" == tmp) || ("--list-all" == tmp)) {
				jlu::printTask (jlu::TaskType::all, contentFile);
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
			} else if (("-c" == tmp) || ("--change" == tmp)) {
				int idTask = 0;
				std::istringstream iss (argv[i + 1]);
				if (iss >> idTask) {
					jlu::changeTask (contentFile, idTask);
				} else {
					//@todo log error
				}
				break;
			} else if (("-s" == tmp) || ("--search" == tmp)) {
				if (3 == argc) {
					jlu::searchTask (contentFile, argv[i + 1]);
					break;
				}
			} else {
				std::cerr << "Argument not valid [" << tmp << "]" << std::endl;
			}
		}
	} else {
		jlu::showHelp ();
	}
	return EXIT_SUCCESS;
}
