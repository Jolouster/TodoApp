#include "manageTask.h"

namespace jlu {
	ManageTask::ManageTask () {
		setTodoFileName (TODO_FILE);
		setDoneFileName (DONE_FILE);
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
		contentFile.push_back (newTask);
		return saveDataInFile (contentFile, TODO_FILE);
	}

	bool ManageTask::removeTask (const int idTask) {
		contentFile.erase (contentFile.begin () + idTask);
		return saveDataInFile (contentFile, TODO_FILE);
	}

	bool ManageTask::doneTask (const int idTask) {
		std::string done = "x " + actualDateTimeToStr () + " " + contentFile[idTask];
		contentFile[idTask] = done;
		return saveDataInFile (contentFile, TODO_FILE);
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

		return saveDataInFile (auxiliar, DONE_FILE) && saveDataInFile (contentFile, TODO_FILE);
	}

	bool ManageTask::changeTask (const std::string& newTask, const int idTask) {
		contentFile[idTask] = actualDateTimeToStr () + " " + newTask;
		return saveDataInFile (contentFile, TODO_FILE);
	}

	std::string ManageTask::actualDateTimeToStr () {
		auto now = std::chrono::system_clock::now ();
		auto in_time_t = std::chrono::system_clock::to_time_t (now);
		std::stringstream ss;
		ss << std::put_time (std::localtime (&in_time_t), DATETIME_FORMAT);
		return ss.str ();
	}
	// --- ends edition

}   // namespace jlu