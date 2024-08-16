#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	char *const args[4] ={"wc", " -l"};
	execv("/usr/bin/wc",args);
}