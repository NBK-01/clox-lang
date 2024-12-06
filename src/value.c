


#include "../headers/mem.h"
#include <stdio.h>
#include "../headers/value.h"

void	init_value_array(t_value_array *arr)
{
	arr->values = NULL;
	arr->count = 0;
	arr->capacity = 0;
}

void	write_value_array(t_value_array *arr, Value val)
{
	int	old_cap;

	if (arr->capacity < arr->count + 1)
	{
		old_cap = arr->capacity;
		arr->capacity = GROW_CAPACITY(old_cap);
		arr->values = GROW_ARR(Value, arr->values,
				old_cap, arr->capacity);
	}
	arr->values[arr->count] = val;
	arr->count++;
}

void	free_value_array(t_value_array *arr)
{
	FREE_ARR(Value, arr->values, arr->capacity);
	init_value_array(arr);
}

void inline	print_value(Value val) { printf("%g", val); }	
