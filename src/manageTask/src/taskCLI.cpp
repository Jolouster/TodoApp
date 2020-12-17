#include "taskCLI.h"

namespace jlu {

	void TaskCliViewer::printLine (const int& count, const std::string& line) {
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

	void TaskCliViewer::printLine (const int& count, const std::string& line, std::string color) {
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

	void TaskCliViewer::printTask (TaskType type) {
		int count = 0, todos = 0, dones = 0;
		std::cout << "     ID     DESCRIPTION\n";
		std::cout << "    ----------------------------------------------" << std::endl;

		if (task.contentFile.empty ()) {
			std::cout << "    The task list is empty" << std::endl;
		} else {
			for (std::string& line : task.contentFile) {
				if (type == TaskType::todo) {
					if (task.isTodo (line)) {
						printLine (count, line);
						todos++;
					} else {
						dones++;
					}
				} else if (type == TaskType::done) {
					if (task.isDone (line)) {
						printLine (count, line, GRAY);
						dones++;
					} else {
						todos++;
					}
				} else if (type == TaskType::all) {
					if (task.isTodo (line)) {
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

	void TaskCliViewer::showHelp () {
		//@todo: write a good help text
		std::string help;
		help = "How to use this program";
		std::cout << help << std::endl;
	}

	void TaskCliViewer::printChangeTask (const int idTask) {
		std::cout << "Old [ID:" << idTask << "] = \"" << task.contentFile[idTask] << "\""
				  << std::endl;
		std::cout << "New: ";
		std::string newTask;
		std::getline (std::cin, newTask);

		if (task.changeTask (newTask, idTask)) {
			std::cout << "-----\nTask changed successfully" << std::endl;
		}
	}

	void TaskCliViewer::printSearchTask (const std::string& patternStr) {
		std::map<int, std::string> auxiliar = task.searchStr (task.contentFile, patternStr);

		std::cout << "     ID     DESCRIPTION\n";
		std::cout << "    ----------------------------------------------" << std::endl;

		for (auto it = auxiliar.begin (); it != auxiliar.end (); it++) {
			if (isDone (it->second)) {
				printLine (it->first, it->second, GRAY);
			} else {
				printLine (it->first, it->second);
			}
		}
	}

	void TaskCliViewer::printClassificationItemsList (const std::string& type) {
		std::vector<std::string> itemsList;
		std::string header;

		if ("tag" == type) {
			itemsList = task.getClassificationTagsList (task.contentFile, "tag");
			header = "TAGS";
		} else if ("project" == type) {
			itemsList = task.getClassificationTagsList (task.contentFile, "project");
			header = "PROJECTS";
		} else if ("context" == type) {
			itemsList = task.getClassificationTagsList (task.contentFile, "context");
			header = "CONTEXTS";
		}
		std::cout << "    " << header << std::endl;
		std::cout << "    ----------------------------------------------" << std::endl;

		if (itemsList.empty ()) {
			std::cout << "    - list empty" << std::endl;
		} else {
			for (std::string tmp : itemsList) {
				std::cout << "     " << tmp << std::endl;
			}
		}
	}

	void TaskCliViewer::printTaskByClassification (const std::string& item,
												   const std::string& type) {
		std::map<int, std::string> itemsList;
		std::string header;

		if ("tag" == type) {
			itemsList = task.taskByClassification (task.contentFile, item,
												   ManageTask::TaskClassification::tag);
			header = "TAG";
		} else if ("project" == type) {
			itemsList = task.taskByClassification (task.contentFile, item,
												   ManageTask::TaskClassification::project);
			header = "PROJECT";
		} else if ("context" == type) {
			itemsList = task.taskByClassification (task.contentFile, item,
												   ManageTask::TaskClassification::context);
			header = "CONTEXT";
		}
		std::cout << "    TASK BY " << header << ": " << item << std::endl;
		std::cout << "    ----------------------------------------------" << std::endl;

		if (itemsList.empty ()) {
			std::cout << "    - list empty" << std::endl;
		} else {
			for (auto it = itemsList.begin (); it != itemsList.end (); it++) {
				printLine (it->first, it->second);
			}
		}
	}
}	// namespace jlu
