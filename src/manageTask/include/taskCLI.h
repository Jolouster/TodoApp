#ifndef TASKCLI_H
#define TASKCLI_H

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

#include "manageTask.h"

namespace jlu {
	enum TaskType { todo, done, all };

	class TaskCliViewer : public ManageTask {
	   public:
		void showHelp ();
		void printTask (TaskType type);
		void printChangeTask (const int idTask);
		void printSearchTask (const std::string& patternStr);
		void printClassificationItemsList (const std::string& type);
		void printTaskByClassification (const std::string& item, const std::string& type);

	   private:
		void printLine (const int& count, const std::string& line);
		void printLine (const int& count, const std::string& line, std::string color);
		ManageTask task;
	};
}	// namespace jlu

#endif	 // TASKCLI_H
