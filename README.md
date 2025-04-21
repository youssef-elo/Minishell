Minishell is a UNIX shell written in c language, it replicates bash behavior emphasizing on rigorous error handling, command parsing, process execution, pipes, output and input redirections and signal handling.

Parsing:
	• Syntax errors checking.
	• Spliting input into tokens depending on their type.
	• Handling different Quoting ' ".
	• Redirection checking.

Execution:
	• Builtin commands inpeentation (cd, echo, export, env, exit, pwd, unset).
	• Environement variable maintenance updating using export and unset.
	• Executing commands using fork() and execve() and collecting their exit status.
	• Exit status updating when each command is executed.
	• Implementing pipes between processes using the pipe() and dup2() commands to link processes input and output to the pipe.
	• Signal handling SIGINT(redisplay of the promp) SIGQUIT(ignored) EOF		(exiting the shell).
	• Redirecting proccesses input and output to the correspoding redirection set in the command  
	">" output redirection without appending erasing all previous file contents.
	">>" appending output to the specified file.
	"<" input redirection , process input is the file content.
	"<<" heredoc implementation a temporary file is created user input is added to the file which will be the input of the command.