//
// urban: a optimizing Brainfsck compiler
// (c) Kied Llaentenn
// See the LICENSE for more information
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MV_B	0	// ^
#define MV_R	1 	// >
#define	MV_L	2	// <
#define	LOOP_S	3	// [
#define	LOOP_E	4	// ]
#define	INC	5	// +
#define	DEC	6	// -
#define	PUTOUT	7	// .
#define	PUTERR	8	// &
#define	READ	9	// ,
#define	NILIFY	10	// *
#define	COMMENT 11	// ;
#define	BF_EXIT	12	// %

typedef struct Instruction
{
	int command_t;
	unsigned int count;
} Instruction;

void usage ( void );
void print_indent ( int no );
void print_command ( int *ident, Instruction i );
int  get_command_t ( char instruction );

int
main ( int argc, char *argv[]  )
{
	if (argc < 2) usage();

	char *path = (char*) malloc(strlen(argv[1]) * sizeof(char));
	strcpy(path, argv[1]);

	// check if file exists
	struct stat stats;
	if (stat(path, &stats) != 0)
	{
		fprintf(stderr, "urban: cannot stat %s: ", path);
		perror("stat()");
		return 1;
	}

	// read file into buffer
	FILE *file = fopen(path, "r");
	unsigned long flen = 0;
	char *buffer;

	if (file == NULL)
	{
		fprintf(stderr, "urban: cannot open %s: ", path);
		perror("fopen()");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	flen = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = (char*) malloc(sizeof(char) * flen);
	if (buffer)
	{
		fread(buffer, 1, flen, file);
	}
	fclose(file);

	// iter over buffer, reading it into an array of Instructions
	// alloc 1 instructions, realloc as needed
	Instruction *instructions = (Instruction*) malloc(sizeof(Instruction) * 10000);
	int ctr = 0;
	while (*buffer)
	{
		int ins_ctr = 0;
		char orig, current = *buffer;

		// comments
		if (current == ';')
		{
			*buffer--;
			if (*buffer != '\\') // escape
			{
				*buffer++;
				while (current != '\n') {
					*buffer++;
					orig, current = *buffer;
				}
				continue;
			}
		}

		while (*buffer && current != orig)
		{
			*buffer++;
			current = *buffer;
			ins_ctr += 1;
		}

		// append to instructions
		realloc(instructions, (sizeof(*instructions) / sizeof(Instruction) + 1));
		instructions[ctr].command_t = get_command_t(*buffer);
		instructions[ctr].count = ins_ctr;

		*buffer++;
	}

	// emit C code
	int inden = 1;
	fprintf(stdout, "#include <stdio.h>\nint \nmain( void )\n{\n");
	print_indent(inden);
	fprintf(stdout, "char buf[30000] = {0};\n");
	print_indent(inden);
	fprintf(stdout, "char *p = buf;\n");
	for (int c = 0; c < (sizeof(*instructions) / sizeof(Instruction) + 1); c++)
		print_command(&inden, instructions[c]);

	// cleanup
	free(instructions);
	//free(buffer);
	free(path);
}

void
usage ( void )
{
	fprintf(stderr, "usage: urban [file]\n");
	exit(1);
}

void
print_indent ( int no )
{
	for (int i = 0; i < no; i++)
	{
		fprintf(stdout, "    ");
	}
}

void
print_command ( int *ident, Instruction i )
{
	switch (i.command_t)
	{
		case MV_B:
			print_indent(*ident);
			fprintf(stdout, "p = 0;\n");
			break;
		case MV_R:
			print_indent(*ident);
			fprintf(stdout, "p += %i;\n", i.count);
			break;
		case MV_L:
			print_indent(*ident);
			fprintf(stdout, "p -= %i;\n", i.count);
			break;
		case LOOP_S:
			print_indent(*ident);
			fprintf(stdout, "while (*p) {\n");
			ident += 1;
			break;
		case LOOP_E:
			ident -=1;
			print_indent(*ident);
			fprintf(stdout, "}\n");
			break;
		case INC:
			print_indent(*ident);
			fprintf(stdout, "*p += %i;\n", i.count);
			break;
		case DEC:
			print_indent(*ident);
			fprintf(stdout, "*p += %i;\n,", i.count);
			break;
		case PUTOUT:
			print_indent(*ident);
			fprintf(stdout, "putchar(*p);\n");
			break;
		case PUTERR:
			print_indent(*ident);
			fprintf(stdout, "fprintf(stderr, \"%c\", *p);\n");
			break;
		case READ:
			print_indent(*ident);
			fprintf(stdout, "*p = getchar();\n");
			break;
		case NILIFY:
			print_indent(*ident);
			fprintf(stdout, "*p = 0;\n");
			break;
		case COMMENT:
			break;
		case BF_EXIT:
			print_indent(*ident);
			fprintf(stdout, "exit((int)*p);\n");
			break;
		default: break;
	}
}

int
get_command_t ( char instruction )
{
	switch (instruction)
	{
		case '^': return MV_B;			// ^
		case '>': return MV_R;			// >
		case '<': return MV_L;			// <
		case '[': return LOOP_S;		// [
		case ']': return LOOP_E;		// ]
		case '+': return INC;			// +
		case '-': return DEC;			// -
		case '.': return PUTOUT;		// .
		case '&': return PUTERR;		// &
		case ',': return READ;			// ,
		case '*': return NILIFY;		// *
		case ';': return COMMENT;		// ;
		case '%': return BF_EXIT;		// %
	}
}


