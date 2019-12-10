// Emit C representation
// of Brainfsck/Urban commands

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emit.h"
#include "inst.h"

// parse the assembly and sent it to
// assm2c() to do the actual converting
// then print it out
void
emit ( struct Instruction *ins )
{
	int x = 0;
	while (ins[x].command != NULL)
	{
		fprintf(stderr, "%s %i %i\n", ins[x].command, ins[x].arg1, ins[x].arg2);
		char *res = assm2c(ins[x].command,
				ins[x].arg1,
				ins[x].arg2);	
		fprintf(stdout, "%s", res);
		free(res);
		++x;
	}
}

// here, we do that actual converting
char*
assm2c ( char *in, int arg1, int arg2 )
{
	if (strcmp(in, "initpt"))
		return "p = 0;\n";
	if (strcmp(in, "incptr")) {
		char *dest = malloc(15);
		sprintf(dest, "p += %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "decptr")) {
		char *dest = malloc(15);	
		sprintf(dest, "p -= %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "startl"))
		return "while (*p) {\n";
	if (strcmp(in, "exitlp"))
		return "}\n";
	if (strcmp(in, "incval")) {
		char *dest = malloc(15);
		sprintf(dest, "(*p) += %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "decval")) {
		char *dest = malloc(15);
		sprintf(dest, "(*p) -= %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "putout"))
		return "putchar(*p);\n";
	if (strcmp(in, "puterr"))
		return "fprintf(stderr, \"%c\", *p);\n";
	if (strcmp(in, "getval"))
		return "*p = readch();\n";
	if (strcmp(in, "delval"))
		return "*p = 0;\n";
	// scan (eq of `[<]` or of `[>]`)
	if (strcmp(in, "scanlt"))
		return "p -= (char*)((void*) *p - memrchr(p, 0, p + 1));\n";
	if (strcmp(in, "scanrt"))
		return "p += (char*)(memchr(*p, 0, sizeof(p)) - (void*)(*p));\n";
	if (strcmp(in, "endapp"))
		return "exit((int)*p);\n";
	if (strcmp(in, "startc"))
	        return "if (*p) {\n";
	if (strcmp(in, "endcnd"))
		return "}\n";
	if (strcmp(in, "cpyval"))
		fprintf(stderr, "not implemented %i\n", arg2);
	return "unknown";
}
