# Minishell
A UNIX command-line interpreter
42 School Project | Systems Programming in C

# 🌐 Overview
Minishell is a lightweight UNIX shell supporting basic command execution, pipelines, redirections, and environment management. Developed in C as part of the 42 curriculum, it demonstrates mastery of:

✔️ Process creation (fork, execve)

✔️ File descriptor management

✔️ Signal handling

✔️ Memory management

# 🎯 Features

Core Functionality

• Command execution (e.g., ls -la, ./my_program)

• History navigation (Up/Down keys)

• Leak-free

• Built-ins:

	echo, cd, pwd, exit
	
	export, unset, env

• Redirections:

        > (overwrite), >> (append)
        < (input), << (heredoc)

• Pipes: 
	
 	cmd1 | cmd2 | cmd3

• Environment variables: 

 	$VAR expansion

# 📡 Signal Handling

SIGINT (Ctrl+C)		Interrupts foreground process/ redisplay prompt 

SIGQUIT (Ctrl+ \\)	IGNORED

CTRL + D		Graceful shell exit  

#  Error handling

   syntax errors

   command not found

   file not found

# ✅ Compliance
42 Norminette: Strict coding style

Error Handling:

Invalid syntax

Permission denied

Ambiguous redirects

No Leaks: Verified with Valgrind
