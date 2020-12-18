#include "taskCLI.h"
#include <regex>

namespace jlu {

	void TaskCliViewer::printLine (const int& count, const std::string& line) {
		const std::regex pattern (R"(^\d\d\d\d-\d\d-\d\d \d\d:\d\d)");

		if (std::regex_search (line, pattern)) {
			std::string dateTime = line.substr (0, 16);
			std::string taskDescription = line.substr (16);
			highlightTags (taskDescription);
			std::cout << "    " << count << ".-  " << RYELOW << dateTime << BLACK << taskDescription
					  << std::endl;
		} else {
			std::string tmpLine (line);
			highlightTags (tmpLine);
			std::cout << "    " << count << ".-  " << tmpLine << std::endl;
		}
	}

	void TaskCliViewer::printLine (const int& count, const std::string& line, std::string color) {
		std::regex patternWithDate (R"(^\d\d\d\d-\d\d-\d\d \d\d:\d\d)");
		std::regex patDoneWithDates (
			R"(^x \d\d\d\d-\d\d-\d\d \d\d:\d\d \d\d\d\d-\d\d-\d\d \d\d:\d\d)");

		if (std::regex_search (line, patternWithDate)) {
			std::string dateTime = line.substr (0, 16);
			std::string taskDescription = line.substr (16);
			highlightTags (taskDescription);
			std::cout << "    " << count << ".-  " << RYELOW << dateTime << color << taskDescription
					  << BLACK << std::endl;
		} else if (std::regex_search (line, patDoneWithDates)) {
			std::string xStr = line.substr (0, 2);	 // include a space
			std::string endDateTime = line.substr (2, 16);
			std::string startDateTime = line.substr (18, 17);	// include a space
			std::string taskDesc = line.substr (35);
			highlightTags (taskDesc);
			std::cout << "    " << count << ".-  ";
			std::cout << GREEN << xStr << BLACK;
			std::cout << RGREEN << endDateTime << RYELOW << startDateTime;
			std::cout << color << taskDesc << BLACK << std::endl;
		} else {
			std::string tmpLine (line);
			highlightTags (tmpLine);
			std::cout << "    " << count << ".-  " << color << tmpLine << BLACK << std::endl;
		}
	}

	void TaskCliViewer::highlightTags (std::string& taskDescription) {
		styleTag (taskDescription);
		styleContext (taskDescription);
		styleProject (taskDescription);
	}

	void TaskCliViewer::styleTag (std::string& taskDescription) {
		std::regex pattern (R"(\s\#[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		std::smatch match;

		if (std::regex_search (taskDescription, match, pattern)) {
			for (std::string tag : match) {
				std::size_t startPos = taskDescription.find (tag.substr (1));
				taskDescription.replace (startPos, tag.substr (1).length (),
										 BLUE + tag.substr (1) + BLACK);
			}
		}
	}

	void TaskCliViewer::styleContext (std::string& taskDescription) {
		std::regex pattern (R"(\s\@[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		std::smatch match;

		if (std::regex_search (taskDescription, match, pattern)) {
			for (std::string tag : match) {
				std::size_t startPos = taskDescription.find (tag.substr (1));
				taskDescription.replace (startPos, tag.substr (1).length (),
										 RED + tag.substr (1) + BLACK);
			}
		}
	}

	void TaskCliViewer::styleProject (std::string& taskDescription) {
		std::regex pattern (R"(\s\+[a-zA-Z0-9\-\_ñáéíóúäëïöüÁÉÍÓÚ]+)");
		std::smatch match;

		if (std::regex_search (taskDescription, match, pattern)) {
			for (std::string tag : match) {
				std::size_t startPos = taskDescription.find (tag.substr (1));
				taskDescription.replace (startPos, tag.substr (1).length (),
										 VIOLET + tag.substr (1) + BLACK);
			}
		}
	}

	void TaskCliViewer::printTask (TaskType type) {
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
		if (todos > 0 || dones > 0) {
			int percent = 0;
			if (dones == 0) {
				percent = 0;
			} else {
				percent = ((dones * 100) / (todos + dones));
			}
			std::cout << "\n    -----------\n    TO-DO: " << VIOLET << todos << BLACK
					  << " DONE: " << GREEN << dones << BLACK << " TOTAL: " << BLUE
					  << (todos + dones) << BLACK << " - " << CYAN << percent << "% " << BLACK
					  << "DONE!" << std::endl;
		}
	}

	void TaskCliViewer::showHelp () {
		//@todo: write a good help text
		std::string help;
		help = "How to use this program";
		std::cout << help << std::endl;
	}

	void TaskCliViewer::printChangeTask (const int idTask) {
		std::cout << "Old [ID:" << idTask << "] = \"" << contentFile[idTask] << "\"" << std::endl;
		std::cout << "New: ";
		std::string newTask;
		std::getline (std::cin, newTask);

		if (changeTask (newTask, idTask)) {
			std::cout << "-----\nTask changed successfully" << std::endl;
		}
	}

	void TaskCliViewer::printSearchTask (const std::string& patternStr) {
		std::map<int, std::string> auxiliar = searchStr (contentFile, patternStr);

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
			itemsList = getClassificationTagsList (contentFile, "tag");
			header = "TAGS";
		} else if ("project" == type) {
			itemsList = getClassificationTagsList (contentFile, "project");
			header = "PROJECTS";
		} else if ("context" == type) {
			itemsList = getClassificationTagsList (contentFile, "context");
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
			itemsList =
				taskByClassification (contentFile, item, ManageTask::TaskClassification::tag);
			header = "TAG";
		} else if ("project" == type) {
			itemsList =
				taskByClassification (contentFile, item, ManageTask::TaskClassification::project);
			header = "PROJECT";
		} else if ("context" == type) {
			itemsList =
				taskByClassification (contentFile, item, ManageTask::TaskClassification::context);
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
