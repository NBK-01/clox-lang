#ifndef VALUE_H
#define VALUE_H

#include "main.h"

typedef double Value;

typedef struct s_value_array
{	
	int		capacity;
	int		count;
	Value	*values;
}	t_value_array;


void	init_value_array(t_value_array *arr);
void	free_value_array(t_value_array *arr);
void	write_value_array(t_value_array *arr, Value val);
void	print_value(Value val);

#endif
