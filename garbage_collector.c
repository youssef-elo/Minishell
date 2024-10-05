#include "minishell.h"

void gc_free(t_mblock *head)
{
	t_mblock *tmp;
	
	while (head)
	{
		free(head->ptr);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void *gc_handler(int s ,int action)
{
	static t_mblock *head_mblock;
	void *ptr;
	t_mblock *new_mblock;
	
	if(action == FREE)
		gc_free(head_mblock);
	else
	{
		ptr = malloc(s);
		if(!ptr)
		{
			gc_handler(0, FREE);
			return(NULL);
		}
		new_mblock = malloc(sizeof(t_mblock));
		if(!new_mblock)
		{
			gc_handler(0, FREE);
			return (NULL);
		}
		new_mblock->ptr = ptr;
		new_mblock->next = head_mblock;
		head_mblock = new_mblock;
		return (ptr);	
	}
	return (NULL);
}
