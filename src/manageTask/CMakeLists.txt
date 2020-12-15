add_library(ManageTask STATIC
	src/filterTask.cpp
	src/manageTaskFile.cpp
	src/manageTask.cpp
	src/taskCLI.cpp
)

target_include_directories(ManageTask PUBLIC include)
