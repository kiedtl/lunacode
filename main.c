//
// urban: a optimizing Brainfsck compiler
// (c) Kied Llaentenn
// See the LICENSE for more information
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

enum commands
{
	mv_b,		// ^
	mv_r,		// >
	mv_l,		// <
	loop_s,		// [
	loop_e,		// ]
	inc,		// +
	dec,		// -
	putout,		// .
	puterr,		// &
	read,		// ,
	nilify,		// *
	comment,	// ;
	bf_exit		// %
};

typedef struct Instruction
{
	int command_t;
	unsigned int count;
} Instruction;

void usage ( void );

int
main ( int argc, char *argv[]  )
{
	if (argc < 2) usage();

	char *path = (char*) malloc(strlen(argv[1]) * sizeof(char));
	strcpy(path, argv[1]);

	// check if file exists
	if (stat(path, NULL) != 0) {
		fprintf(stderr, "urban: cannot stat %s: ", path);
		perror("stat()");
		return 1;
	}

	// read file into buffer
}

void
usage ( void )
{
	fprintf(stderr, "usage: urban [file]\n");
	exit(1);
}
