#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assm.h"

#define TRUE 1

char*
b2asm ( char *bf )
{
	// realloc as needed
	char *dest = malloc(1);

	int i = 0;
	int bflen = strlen(bf);
	while (i < bflen)
	{
		// eq to <value> for compressable commands
		// (+,-,<,>,), eq to <src> for `cpyval`
		int arg1 = 0;

		// eq to <dest> for cpyval command
		int arg2 = 0;

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
			while (TRUE)
			{
				++arg1;
				++i;
				if (bf[i] != bf[origctr])
				{
					i -= 2;
					arg1 -= 2;
					break;
				}
				else
					continue;
			}
		}

		char* command = get_asm(bf[i]);

		// TODO: stage 5-6 opts

		// append to dest as command
		char arg1s[(int)(ceil(log10(arg1)) + 1)];
		char arg2s[(int)(ceil(log10(arg2)) + 1)];

		sprintf(arg1s, "%i", (int)arg1s);
		sprintf(arg2s, "%i", (int)arg2s);

		realloc(dest, (strlen(dest) + strlen(command)
					+ strlen((const char*)&arg1s)
					+ strlen((const char*)&arg2s)
					+ 3));
		strcat(dest, command);
		strcat(dest, " ");
		strcat(dest, (const char*)&arg1s);
		strcat(dest, " ");
		strcat(dest, (const char*)&arg2s);
		strcat(dest, "\n");
	}
	return dest;
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
