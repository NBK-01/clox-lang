#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"

void	disassemble_chunk(t_chunk *chunk, const char *name);
int		disassemble_instruction(t_chunk *chunk, int offset);

#endif 
