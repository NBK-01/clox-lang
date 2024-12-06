#ifndef CHUNK_H
#define CHUNK_H

#include "main.h"
#include "value.h"

/*op => operation code*/
typedef enum e_op_code
{
	OP_CONSTANT,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NEGATE,
	OP_RETURN,
}	t_op_code;

/**/
/*rolling custom dynamic array => (*code) is the array.*/
/*	- no of allocated elems in array in (capacity).*/
/*	- no of elements from allocated allocated capacity in use (count).*/

 /*
  * if chunk array has capacity = 4 and count = 3
  *		- adding new elem will result in inserting into array and count + 1;
  *  	(simple)
  *	
  *	if chunk array has filled up capacity ie: (cap = 4, count = 4) then we take these steps.
  *		- alloc brand new arr with larger cap (according to need or just double it)
  *		- copy all elems from old arr to new arr.
  *		- store new cap.
  *		- delete and free old arr.
  *		- update code to point to the new arr.
  *		- store new elem in new arr.
  *		- update count.
  *
  * */
typedef struct s_chunk
{
	int				count;
	int				capacity;
	uint8_t			*code;
	t_value_array	constants;
	int				*lines;
}	t_chunk;


/******************************************/
/*****			FUNCTIONS			  *****/
/******************************************/
void	init_chunk(t_chunk *chunk);
void	free_chunk(t_chunk *chunk);
void	write_chunk(t_chunk *chunk, uint8_t byte, int line);
int		add_constant(t_chunk *chunk, Value val);

#endif
