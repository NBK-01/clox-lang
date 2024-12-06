#ifndef MEM_H
#define MEM_H

#include "main.h"

/*macro to grow capacity by x2
 *	- add capacity of 8 when we start from and x2 everytime we need more
 *	*/
#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

/*macro to grow arr to needed sizeof
 *	- determines type and size of elems to add
 *	*/
#define GROW_ARR(type, ptr, old_count, new_count) \
	(type *)re_alloc(ptr, sizeof(type) * (old_count), \
			sizeof(type) * (new_count))

/* Free array and init an empty arr
 * 
 * */
#define FREE_ARR(type, ptr, old_count) \
	re_alloc(ptr, sizeof(type) * (old_count), 0)

/* this will alloc and free most of the mem used in this project
 *	- if old_size = 0 and new is > 0 we alloc a new block.
 *	- if old_size > 0 and new is = 0 we free alloc.
 *	- if old_size > 0 and new < old we shrink alloc.
 *	- if old_size > 0 and new > old we grow alloc.
 *	*/
void	*re_alloc(void *ptr, size_t old_size, size_t new_size);

#endif
