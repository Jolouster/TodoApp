#include <gtest/gtest.h>
#include <iostream>
#include "filterTask.h"

TEST (FilterTodoTasks, checkTodo) {
	jlu::FilterTask filter;

	std::string taskList1[] = {
		"2020-12-11 Tarea de ejemplo 1 @casa +todoApp",
		"xTarea ejemplo 2 +familia",
		"XDirect tarea 3",
		"2020-12-11 Tarea 4 +todoApp @oficina",
		"2020-12-11 10:20 Tarea5",
	};
	for (std::string task : taskList1) {
		ASSERT_TRUE (filter.isTodo (task));
	}

	std::string taskList2[] = {
		"x 2020-12-11 Tarea de ejemplo 1 @todoApp",
		"x Tarea ejemplo 2",
		"x +casa pintar habitación",
		"x 2020-12-11 2020-12-10 Tarea ejemplo 3 @oficina +todoApp",
		"x 2020-12-12 2020-12-11 Recoger zapatero",
		"",
	};
	for (std::string task : taskList2) {
		ASSERT_FALSE (filter.isTodo (task));
	}
}

TEST (FilterTodoTasks, checkDoneTask) {
	jlu::FilterTask filter;

	std::string taskList1[] = {
		"2020-12-11 Tarea de ejemplo 1 @casa +todoApp",
		"xTarea ejemplo 2 +familia",
		"XDirect tarea 3",
		"2020-12-11 Tarea 4 +todoApp @oficina",
		"2020-12-11 10:20 Tarea5",
		"",
	};
	for (std::string task : taskList1) {
		ASSERT_FALSE (filter.isDone (task));
	}

	std::string taskList2[] = {
		"x 2020-12-11 Tarea de ejemplo 1 @todoApp",
		"x Tarea ejemplo 2",
		"x +casa pintar habitación",
		"x 2020-12-11 2020-12-10 Tarea ejemplo 3 @oficina +todoApp",
		"x 2020-12-12 2020-12-11 Recoger zapatero",
	};
	for (std::string task : taskList2) {
		ASSERT_TRUE (filter.isDone (task));
	}
}
