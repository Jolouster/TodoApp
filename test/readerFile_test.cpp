#include "readerFile.h"
#include <gtest/gtest.h>

TEST (ReaderTodoFile, checkEmptyOutput) {
	std::vector<std::string> output = jlu::getContent ("FileNoExists");
	ASSERT_EQ (0, output.size ());
}

TEST (ReaderTodoFile, checkSizeOutput) {
	std::ifstream file ("/home/jlopez/Proyectos/TodoApp/test/todoTest.txt");
	int count = 0;
	std::string tmp;
	while (std::getline (file, tmp)) {
		count++;
	}
	file.close ();

	std::vector<std::string> output =
		jlu::getContent ("/home/jlopez/Proyectos/TodoApp/test/todoTest.txt");
	ASSERT_EQ (count, output.size ());
}
