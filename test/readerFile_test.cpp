#include <gtest/gtest.h>
#include "manageTaskFile.h"

TEST (ReaderTodoFile, checkEmptyOutput) {
	jlu::ManageTaskFile mFile;
	std::vector<std::string> output = mFile.getContent ("FileNoExists");
	ASSERT_EQ (0, output.size ());
}

TEST (ReaderTodoFile, checkSizeOutput) {
	jlu::ManageTaskFile mFile;

	std::ifstream file ("/home/jlopez/Proyectos/TodoApp/test/todoTest.txt");
	int count = 0;
	std::string tmp;
	while (std::getline (file, tmp)) {
		count++;
	}
	file.close ();

	std::vector<std::string> output =
		mFile.getContent ("/home/jlopez/Proyectos/TodoApp/test/todoTest.txt");
	ASSERT_EQ (count, output.size ());
}
