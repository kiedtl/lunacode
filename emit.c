// Emit C representation
// of Brainfsck/Urban commands

#include <stdio.h>

void
print_command ( int count, char i )
{
	switch (i)
	{
		case '^':
			fprintf(stdout, "p = 0;\n");
			break;
		case '>':
			fprintf(stdout, "p += %i;\n", count);
			break;
		case '<':
			fprintf(stdout, "p -= %i;\n", count);
			break;
		case '[':
			fprintf(stdout, "while (*p) {\n");
			break;
		case ']':
			fprintf(stdout, "}\n");
			break;
		case '+':
			fprintf(stdout, "(*p) += %i;\n", count);
			break;
		case '-':
			fprintf(stdout, "(*p) -= %i;\n", count);
			break;
		case '.':
			fprintf(stdout, "putchar(*p);\n");
			break;
		case '&':
			fprintf(stdout, "fprintf(stderr, \"%%c\", *p);\n");
			break;
		case ',':
			fprintf(stdout, "*p = readch();\n");
			break;
		case '*':
			fprintf(stdout, "*p = 0;\n");
			break;
		case ';': break;
		// scan (eq of `[<]` or of `[>]`)
		case '{':
			  fprintf(stdout,
				"p -= (char*)((void*) *p - memrchr(p, 0, p + 1));\n");
			  break;
		case '}': fprintf(stdout,
				"p += (char*)(memchr(*p, 0, sizeof(p)) - (void*)(*p));\n");
		case '@':
			fprintf(stdout, "exit((int)*p);\n");
			break;
		default: break;
	}
}

