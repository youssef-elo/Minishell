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

void	*galloc(int size, int action)
{
	static t_mblock *head;
	void *ptr;
	
	if (action == MALLOC)
	{
		ptr= malloc(size);
		if (!ptr)
		{
			gc_handler(0, FREE);
			gc_free(head);
			exit (1);
		}
		gc_node(ptr, &head);
	}
	else if (action == FREE)
	{
		gc_free(head);
		head = NULL;
	}
	return (NULL);
}

void gc_node(void *ptr, t_mblock **head)
{
	t_mblock	*node;

	node = malloc(sizeof(t_mblock));
	if (!node)
	{
			gc_handler(0, FREE);
			galloc(0, FREE);
			exit (1);
	}
	node->next = *head;
	node->ptr = ptr;
	*head = node;
}

void *gc_handler(int s ,int action)
{
	void *ptr;
	static t_mblock *head;
	
	if(action == FREE)
	{
		gc_free(head);
		head = NULL;
	}
	else if (action == MALLOC)
	{
		ptr = malloc(s);
		if(!ptr)
		{
			gc_handler(0, FREE);
			galloc(0, FREE);
			exit (1);
		}
		gc_node(ptr, &head);
		return (ptr);	
	}
	return (NULL);
}
//to update : garbage collector when allocating you should specify the lifetime of the allocation is it from prompt to prompt or should it last all the time;
//then you call free on all the ones with prompt lifetime when exiting from a prompt to another