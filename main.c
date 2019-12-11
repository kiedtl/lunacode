//
// urban: a optimizing Brainfsck compiler
// (c) Kied Llaentenn
// See the LICENSE for more information
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "inst.h"
#include "emit.h"
#include "opt2.h"
#include "opt3.h"
#include "assm.h"

#define TRUE  1
#define FALSE 0

void usage ( void );
void indent ( int *i, char c );

int
main ( int argc, char *argv[]  )
{
	// TODO: argument parsin
	//if (argc < 2) usage();

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

	buffer = (char*) malloc(sizeof(char) * (flen + 1));
	fread(buffer, 1, flen, file);
	
	// null-terminate the darned buffer
	buffer[flen + 1] = '\0';
	fclose(file);

	// perform stage 2-3 optimizations
	buffer = opt2(buffer);
	buffer = opt3(buffer);

	// default C std
	fprintf(stdout, "#define _GNU_SOURCE\n");
	fprintf(stdout, "#include <stdio.h>\n#include <stdlib.h>\n");
	fprintf(stdout, "#include <string.h>\n\n");

	// static read() function that returns 0 for EOF
	fprintf(stdout, "int\nreadch ( void )\n{\n");
	fprintf(stdout, "    int c = getchar();\n");
	fprintf(stdout, "    return (c != EOF ? c : 0);\n}\n\n");

	// main function
	fprintf(stdout, "int\nmain ( void )\n{\n");
	fprintf(stdout, "    char *mem = (char*) malloc(100000 * sizeof(char));\n");
	fprintf(stdout, "    long p = 0;\n");

	int ilen = 0;
	Instruction *ins = b2asm(buffer, &ilen);
	emit(ins, ilen);

	fprintf(stdout, "\n}\n");

	// cleanup
	if (buffer) free(buffer);
	free(path);
}

void
usage ( void )
{
	fprintf(stderr, "usage: urban [file]\n");
	exit(1);
}
