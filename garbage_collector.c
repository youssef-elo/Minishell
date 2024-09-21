#include "minishell.h"

void *galloc(int size)
{
	if(size == 0)
		return NULL;
	void *new = malloc(size);
	if (!new)
		return NULL;
	return new;
}

int main(){
	char *str = galloc(10);
	sprintf(str, "%s", "012345678");
	printf("%s\n", str);
}