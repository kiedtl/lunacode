#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "assm.h"

#define TRUE 1

struct Instruction*
b2asm ( char *bf )
{
	Instruction *ins = (Instruction*) malloc((strlen(bf) + 1) * sizeof(Instruction*));

	int i = 0; // bf counter
	int x = 0; // ins counter
	int bflen = strlen(bf);
	while (i < bflen)
	{
		// arg1: eq to <value> for compressable commands
		// (+,-,<,>,), eq to <src> for `cpyval`
		// arg2: eq to <dest> for cpyval command
		int arg1 = 1;
		int arg2 = 1;

		// ignore comments
		if (bf[i] == ';')
		{
			while (bf[i] != '\n')
			{
				++i;
			}
			--i;
			continue;
		}

		// compress commands (stage 1 opts)
		if (bf[i + 1] == bf[i]
				&& (bf[i] == '+'
					|| bf[i] == '-'
					|| bf[i] == '<'
					|| bf[i] == '>'
					))
		{
			int origctr = i;
			while (bf[i] != bf[origctr])
			{
				++arg1;
				++i;
			}
		}

		char* command = get_asm(bf[i]);

		// TODO: stage 5-6 opts

		// append to dest as command
		//realloc(dest, (strlen(dest) + strlen(command)
		//			+ strlen((const char*)&arg1s)
		//			+ strlen((const char*)&arg2s)
		//			+ 3));

		// command
		ins[x].command = calloc(strlen(command) + 1, sizeof(char*));
		ins[x].command[strlen(command) + 1] = '\0';
		strcpy(ins[x].command, command);

		fprintf(stderr, "iter: x = %i\tstrlen = %i\n", x, bflen);	
		// instruction arguments
		ins[x].arg1 = *(int*) malloc(1 * sizeof(int));
		ins[x].arg2 = *(int*) malloc(1 * sizeof(int));

		ins[x].arg1 = arg1;
		ins[x].arg2 = arg2;

		++i;
		++x;
	}
	ins[strlen(bf) + 1].command = NULL;
	return ins;
}

char*
get_asm ( char c )
{
	switch (c)
	{
		case '^': return "initpt";
		case '>': return "incptr";
		case '<': return "decptr";
		case '[': return "startl";
		case ']': return "exitlp";
		case '+': return "incval";
		case '-': return "decval";
		case '.': return "putout";
		case '&': return "puterr";
		case ',': return "getval";
		case '*': return "delval";
		case '{': return "scanlt";
		case '}': return "scanrt";
		case '@': return "endapp";
		case '(': return "startc";
		case ')': return "endcnd";
		//case '%': return "cpyval";
		default: return "";
	}
}
