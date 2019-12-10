#ifndef EMIT_INCLUDED
#define EMIT_INCLUDED
#include "inst.h"

void emit ( struct Instruction *ins );
char* assm2c ( char *in, int arg1, int arg2 );

#endif
