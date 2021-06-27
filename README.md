# Simple-Shell (Multi-Processing)

• The command shell takes the user command and its parameter(s), i.e., “ls” and “–l” in this example, and convert them into C strings. 

• The command shell should create a child process via <b>fork()</b>. 

• The child process passes the C strings—the command and parameter(s)—to <b>execvp()</b>. 

• The child exits if <b>execvp()</b> returns error.

• The parent process, i.e., the command shell, should wait, via <b>waitpid()</b>, for the child process to finish. 

• The command shell gets the next command and repeats the above steps. 


The command shell terminates itself when the user types exit. In case a user wants to execute the command in background (i.e. as a background process), he/she writes & at the end of the command. For example, a user command can be: firefox & In this case, your command shell should not wait for the child. a log file kept for the shell program such that whenever a child process terminates, the shell program appends the line “Child process was terminated” to the log file. Using a signal handler that appends the line to the log file when the SIGCHLD signal is received.
