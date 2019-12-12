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
emit ( struct Instruction *ins, int len )
{
	int x = 0;
	int indent = 1;
	while (ins[x].command != NULL && x < len )
	{
		//fprintf(stderr, "%s %i %i\n", ins[x].command, ins[x].arg1, ins[x].arg2);
		if (ins[x].command[0] == 0)
		{
			++x;
			continue;
		}

		// print indentation
		if (strcmp(ins[x].command, "exitlp") == 0)
			--indent;
		for (int c = 0; c < indent; c++)
			fprintf(stdout, "    ");
		if (strcmp(ins[x].command, "startl") == 0)
			++indent;

		// print out C command
		char *res = assm2c(ins[x].command,
				ins[x].arg1,
				ins[x].arg2);	
		fprintf(stdout, "%s", res);
		++x;
	}
}

// here, we do that actual converting
char*
assm2c ( char *in, int arg1, int arg2 )
{
	if (strcmp(in, "initpt") == 0)
		return "p = 0;\n";
	if (strcmp(in, "incptr") == 0) {
		char *dest = malloc(15);
		sprintf(dest, "p += %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "decptr") == 0) {
		char *dest = malloc(15);	
		sprintf(dest, "p += %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "startl") == 0)
		return "while (mem[p]) {\n";
	if (strcmp(in, "exitlp") == 0)
		return "}\n";
	if (strcmp(in, "incval") == 0) {
		char *dest = malloc(15);
		sprintf(dest, "mem[p] += %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "decval") == 0) {
		char *dest = malloc(15);
		sprintf(dest, "mem[p] -=  %i;\n", arg1);
		return dest;
	}
	if (strcmp(in, "putout") == 0)
		return "putchar(mem[p]);\n";
	if (strcmp(in, "puterr") == 0)
		return "fprintf(stderr, \"%c\", mem[p]);\n";
	if (strcmp(in, "getval") == 0)
		return "mem[p] = readch();\n";
	if (strcmp(in, "delval") == 0)
		return "mem[p] = 0;\n";
	// scan (eq of `[<]` or of `[>]`)
	if (strcmp(in, "scanlt") == 0)
		return "p -= (long)((void*) (*mem + p) - memrchr(*mem, 0, p + 1));\n";
	if (strcmp(in, "scanrt") == 0)
		return "p += (long)(memchr(*mem + p, 0, sizeof(*mem)) - (void*)(*mem + p));\n";
	if (strcmp(in, "endapp") == 0)
		return "exit((int)mem[p]);\n";
	if (strcmp(in, "startc") == 0)
	        return "if (mem[p]) {\n";
	if (strcmp(in, "endcnd") == 0)
		return "}\n";
	if (strcmp(in, "cpyval") == 0)
		fprintf(stderr, "not implemented %i\n", arg2);
	return "";
}
