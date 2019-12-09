// Emit C representation
// of Brainfsck/Urban commands

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emit.h"

// parse the assembly and sent it to
// assm2c() to do the actual converting
// then print it out
void
emit ( char *assm )
{
	int i = 0;
	int len = strlen(assm);
	while (i < len && assm[i] != '\n')
	{
		int c = 0;
		char *comm = malloc(7);
		int arg1, arg2 = 0;

		char arg1s[9];
		char arg2s[9];

		// null-terminate the strings!
		comm[6] = '\0';
		arg1s[8] = '\0';
		arg2s[8] = '\0';

		// command
		while (assm[i] != ' ')
		{
			comm[c] = assm[i];
			++c;
			++i;
		}
		++i;
		c = 0;

		// args
		while (assm[i] != ' ')
		{
			arg1s[c] = assm[i];
			++i;
			++c;
		}
		arg1 = atoi(arg1s);
		c = 0;
		++i;

		while (assm[i] != ' ')
		{
			arg2s[c] = assm[i];
			++i;
			++c;
		}
	
		char *res = assm2c(comm, arg1, arg2);	
		fprintf(stdout, "%s", res);
		if (res) free(res);
		if (comm) free(comm);
		++i;
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
	return "";
}
