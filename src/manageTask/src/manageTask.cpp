#include "manageTask.h"

namespace jlu {
	ManageTask::ManageTask () {
		TaskConfig config;
		setTodoFileName (config.getTodoFileName ());
		setDoneFileName (config.getDoneFileName ());
		contentFile = getContent (todoFileName);
	}
	void ManageTask::setTodoFileName (const std::string& name) {
		//@toddo: validate input
		todoFileName = name;
	}

	void ManageTask::setDoneFileName (const std::string& name) {
		//@todo: validate input
		doneFileName = name;
	}

	// Edition
	bool ManageTask::addNewTask (const std::string& newTask) {
		contentFile.push_back (actualDateTimeToStr () + " " + newTask);
		return saveDataInFile (contentFile, todoFileName);
	}

	bool ManageTask::removeTask (const int idTask) {
		contentFile.erase (contentFile.begin () + idTask);
		return saveDataInFile (contentFile, todoFileName);
	}

	bool ManageTask::removeTask (const std::vector<int> idList) {
		for (int index : idList) {
			contentFile.erase (contentFile.begin () + index);
		}
		return saveDataInFile (contentFile, todoFileName);
	}

	bool ManageTask::doneTask (const int idTask) {
		std::string done = "x " + actualDateTimeToStr () + " " + contentFile[idTask];
		contentFile[idTask] = done;
		return saveDataInFile (contentFile, todoFileName);
	}

	bool ManageTask::archiveDoneTasks () {
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

		return saveDataInFile (auxiliar, doneFileName) &&
			   saveDataInFile (contentFile, todoFileName);
	}

	bool ManageTask::changeTask (const std::string& newTask, const int idTask) {
		contentFile[idTask] = actualDateTimeToStr () + " " + newTask;
		return saveDataInFile (contentFile, todoFileName);
	}

	std::string ManageTask::actualDateTimeToStr () {
		auto now = std::chrono::system_clock::now ();
		auto in_time_t = std::chrono::system_clock::to_time_t (now);
		std::stringstream ss;
		ss << std::put_time (std::localtime (&in_time_t), DATETIME_FORMAT);
		return ss.str ();
	}
	// --- ends edition

}	// namespace jlu
