#ifndef MANAGETASK_H
#define MANAGETASK_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include "filterTask.h"
#include "manageTaskFile.h"
#include "taskConfig.h"

#define DATETIME_FORMAT "%F %R"	  // "yyyy-MM-dd HH:mm"
#define TODO_FILE "/home/jlopez/Dropbox/ExBrain/todo.txt"
#define DONE_FILE "/home/jlopez/Dropbox/ExBrain/done.txt"

namespace jlu {
	class ManageTask : public ManageTaskFile, public FilterTask {
	   public:
		ManageTask ();
		void setTodoFileName (const std::string& name);
		void setDoneFileName (const std::string& name);
		// Edition
		bool addNewTask (const std::string& newTask);
		bool removeTask (const int idTask);
		bool removeTask (const std::vector<int> idList);
		bool doneTask (const int idTask);
		bool archiveDoneTasks ();
		bool changeTask (const std::string& newTask, const int idTask);
		std::vector<std::string> contentFile;

	   private:
		std::string actualDateTimeToStr ();

		// Variables
		std::string todoFileName;
		std::string doneFileName;
	};
}	// namespace jlu

#endif	 // MANAGETASK_H
