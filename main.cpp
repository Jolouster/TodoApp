#include <iostream>
#include <sstream>
#include <string>
#include "taskCLI.h"

#define APPLICATION_NAME "TodoApp"
#define APPLICATION_VERSION "1.0.0"

int main (int argc, char* argv[]) {
	jlu::TaskCliViewer task;

	if (1 < argc) {
		std::string tmp;
		for (int i = 1; i < argc; i++) {
			tmp = argv[i];
			if (("-l" == tmp) || ("--list" == tmp)) {
				// list task to do.
				if (2 == argc) {
					task.printTask (jlu::TaskType::todo);
				} else if (3 == argc) {
					task.printSearchTask (argv[i + 1]);
					break;
				}
			} else if (("-la" == tmp) || ("--list-all" == tmp)) {
				task.printTask (jlu::TaskType::all);
			} else if (("-ld" == tmp) || ("--list-done" == tmp)) {
				task.printTask (jlu::TaskType::done);
			} else if (("-a" == tmp) || ("--add" == tmp)) {
				// add new task. Next item must be a text inside of ""
				if ((i + 1) < argc) {
					if (task.addNewTask (argv[i + 1])) {
						std::cout << "-----\nNew task added successfully\n\t" << argv[i + 1]
								  << std::endl;
					} else {
						std::cout << "-----\nFAIL! Any task saved\n" << std::endl;
					}

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
							if (task.removeTask (index)) {
								std::cout << "-----\nTask " << index << " deleted successfully"
										  << std::endl;
							} else {
								std::cout << "-----\nTask " << index << " can't be delete"
										  << std::endl;
							}
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
							if (task.doneTask (index)) {
								// @todo: mostrar una unica tarea por indice
								// std::cout << "-----\nTask " << index << " marked as done\n\t" <<
								// contentFile[index] << std::endl;
							} else {
								std::cout << "-----\nTask " << index << " can't be marked as done\n"
										  << std::endl;
							}
						} else {
							//@todo log error
							break;
						}
					}
					break;
				}
			} else if (("-h" == tmp) || ("--help" == tmp)) {
				task.showHelp ();
			} else if (("-v" == tmp) || ("--version" == tmp)) {
				std::cout << APPLICATION_NAME << " - Version: " << APPLICATION_VERSION
						  << " Compiled: " << __DATE__ << " " << __TIME__ << std::endl;
			} else if (("-ar" == tmp) || ("--archive" == tmp)) {
				if (task.archiveDoneTasks ()) {
					std::cout << "-----\nArchived done tasks in done.txt" << std::endl;
				}
			} else if (("-c" == tmp) || ("--change" == tmp)) {
				int idTask = 0;
				std::istringstream iss (argv[i + 1]);
				if (iss >> idTask) {
					task.printChangeTask (idTask);
				} else {
					//@todo log error
				}
				break;
			} else if (("-s" == tmp) || ("--search" == tmp)) {
				if (3 == argc) {
					task.printSearchTask (argv[i + 1]);
					break;
				}
			} else {
				std::cerr << "Argument not valid [" << tmp << "]" << std::endl;
			}
		}
	} else {
		task.showHelp ();
	}
	return EXIT_SUCCESS;
}
