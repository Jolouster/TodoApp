cmake_minimum_required (VERSION 3.18)

project (TodoApp VERSION 1.0.0 LANGUAGES CXX)

set (CMAKE_BUILD_TYPE Debug)
# set (CMAKE_BUILD_TYPE Release)
set (DEST_LIB_FOLDER "${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib")
set (DEST_APP_FOLDER "${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin")

if (NOT EXISTS ${DEST_LIB_FOLDER})
	file(MAKE_DIRECTORY ${DEST_LIB_FOLDER})
endif()

if (NOT EXISTS ${DEST_APP_FOLDER})
	file(MAKE_DIRECTORY ${DEST_APP_FOLDER})
endif()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DEST_LIB_FOLDER})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DEST_LIB_FOLDER})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DEST_APP_FOLDER})

if("Release" STREQUAL ${CMAKE_BUILD_TYPE})
	include(GNUInstallDirs)
	set(CMAKE_INSTALL_PREFIX "/op/${PROJECT_NAME}")
	option(INCLUDE_GOOGLE_TEST "Don't add Google Test framework to project" False)
else ("Debug" STREQUAL ${CMAKE_BUILD_TYPE})
	add_compile_options(-Wall -Wextra -Wpedantic)
	option(INCLUDE_GOOGLE_TEST "Add Google Test framework to project" True)
endif()


# Add third party source code
# ----------------------------------------------
include(FetchContent)
# - Google Test
if (INCLUDE_GOOGLE_TEST)
	FetchContent_Declare(googletest 
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG master
		SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/googletest
		BINARY_DIR ${PROJECT_BINARY_DIR}/external/googletest
		INSTALL_DIR ${DEST_LIB_FOLDER}
	)

	FetchContent_GetProperties(googletest)

	if(NOT googletest_POPULATED)
		FetchContent_Populate(googletest)
		add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
	endif()
	
endif()
# - end Google Test

add_subdirectory(src/manageTask)

add_executable (dtask main.cpp)
# add_executable (appTest test/main.cpp)

target_link_libraries(dtask PUBLIC ManageTask)

# - At the en of CMakeLists.txt I add test files
if (INCLUDE_GOOGLE_TEST)
	enable_testing()
	add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()
