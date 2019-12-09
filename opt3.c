// Stage 3 optimizations:
// 	- fuse [<]/[>] into {/}

#include <stdlib.h>
#include <string.h>

#include "opt3.h"

char*
opt3 ( char *src )
{
	char *dest = (char*) malloc(sizeof(char) * strlen(src));
	int d = 0;
	int s = 0;
	for (;src[s];)
	{
		if (src[s] == '[' 
				&& (src[s + 1] == '<'
					|| src[s + 1] == '>')	
				&& src[s + 2] == ']')
		{
			if (src[s + 1] == '<')
				dest[d] = '{';
			else if (src[s + 1] == '>')
				dest[d] = '}';
			
			s += 3;
			++d;
			continue;
		}
		else
		{
			dest[d] = src[s];
		}

		++s;
		++d;
	}

	return dest;
}
