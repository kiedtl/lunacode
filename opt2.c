// Stage 2 optimizations:
// 	- fuse [-] into *
// 	- misc loop optimizations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
opt2 ( char *src )
{
	char *dest = (char*) malloc(sizeof(char) * strlen(src));
	int d = 0;
	int s = 0;
	for (;src[s];)
	{
		if (src[s] == '[' 
				&& src[s + 1] == '-' 
				&& src[s + 2] == ']')
		{
			dest[d] = '*';
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
