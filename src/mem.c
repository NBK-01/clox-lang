#include "../headers/mem.h"
#include <stdio.h>

void	*re_alloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*res;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	res = realloc(ptr, new_size);
	if (res == NULL)
	{
		perror("realloc");
		exit (1);
	}
	return (res);
}
