# TodoApp CLI

Application to manage your todo.txt file by a command line interface.

This applications follows the philosophy of manage tasks with plain text and Dropbox following the [todotxt/todo.txt](https://github.com/todotxt/todo.txt) format specifications.

## HOW TO USE

	dtask --comand <argument>

	-a  | --add "New task to do"            Add new task to todo.txt file
	-ar | --archive                         Move all done task to done.txt file
	-c  | --change  N                       Change the task with identifier N (integer)
	-d  | --done    N M L ...				Mark as done the task with identifier N, M, L, etc (integer)
	-h  | --help 							Show this help 
	-l  | --list                            List all task to do with its identifier
	-la | --list-all 						List all task, to do and done, with its identifier
	-ld | --list-done 						List only done task in file todo.txt 
	-r  | --remove N M L O ...  			Remove one o more task from todo.txt file. Where N, M, L, O, etc are the identifier of tasks to delete
	-s  | --search Word 					Search "Word" in task list and list only the tasks have this word
	-v  | --version 						Show the version
	--tag-list 								List all differents tags existent in to do list
	--project-list 							List all differents projects existent in to do list
	--context-list 							List all differents context existent in to do list 
	--by-context contexName                 List all task to do with context 'contextName'
	--by-tag  tagName                       List all task to do with the tag 'tagName'
	--by-project projectName                List all task to do of project 'projectName'

