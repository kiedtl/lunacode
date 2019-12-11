#ifndef ASSM_INCLUDED
#define ASSM_INCLUDED
#include "inst.h"

struct Instruction* b2asm ( char *bf, int *len );
int is_valid_command ( char c );
char* get_asm ( char c );

#endif
