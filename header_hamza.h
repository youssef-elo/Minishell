#ifndef HEADER_HAMZA_H
#define HEADER_HAMZA_H


#include <stdio.h>

typedef struct s_env t_env;
struct s_env
{
	char *key;
	char *value;
	t_env *next;	
};



#endif