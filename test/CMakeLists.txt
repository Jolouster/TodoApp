cmake_minimum_required(VERSION 3.18.0)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

add_executable(appTest ${TEST_SOURCES})

target_include_directories (
	appTest
	PUBLIC
	${PROJECT_SOURCE_DIR}/src/manageTask
)

target_link_libraries (
	app
	PUBLIC
	ManageTask
)

target_link_libraries (
	appTest
	PUBLIC
	gtest_main
	ManageTask
)

add_test(
	NAME TodoApp
	COMMAND appTest
)
