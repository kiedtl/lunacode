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
#include "args.h"

#define VERSION "0.2.0"

void usage ( void );
void version ( void );

// global options
struct Options *opts;
char *argv0;

int
main ( int argc, char *argv[]  )
{
	argv0 = argv[0];
	
	// default options
	opts = (struct Options*) calloc(1, sizeof(struct Options*));
	opts->perf_opt1 = FALSE;
	opts->perf_opt2 = FALSE;
	opts->perf_opt3 = FALSE;

	// parse options (thanks to st dev team :)
	ARGBEGIN {
		case '1':
			opts->perf_opt1 = TRUE;
			break;
		case '2':
			opts->perf_opt2 = TRUE;
			break;
		case '3':
			opts->perf_opt3 = TRUE;
			break;
		case 'v':
			opts->verbose = TRUE;
			break;
		case 'V':
			version();
			break;
		case 'h':
		default:
			usage();
			break;
	} ARGEND;

	// print options if verbose
	if (opts->verbose) {
		fprintf(stderr, "\n----- OPTIONS ------\n");
		fprintf(stderr, "opts->verbose\t\t%i\n", opts->verbose);
		fprintf(stderr, "opts->perf_opt1\t\t%i\n", opts->perf_opt1);
		fprintf(stderr, "opts->perf_opt2\t\t%i\n", opts->perf_opt2);
		fprintf(stderr, "opts->perf_opt3\t\t%i\n", opts->perf_opt3);
	}

	// read stdin to buffer
	FILE *fp = stdin;
	size_t len = 0;
	size_t size = 10000;
	char *buffer = (char*) calloc(size, sizeof(char));
	int ch;

	while (EOF != (ch = fgetc(fp))) {
		++len;
		//buffer[len] = (char) ch;
		char tmpbuf[] = { (char) ch, (char) 0 };
		strncat(buffer, (const char *) tmpbuf, 1);
		if (len == size) {
			size += 10;
		        buffer = (char*) realloc(buffer, size);
		}
	}

	++len;
	buffer[len] = (char) 0;

	// perform stage 2-3 optimizations
	if (opts->perf_opt2) buffer = opt2(buffer);
	if (opts->perf_opt3) buffer = opt3(buffer);

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
}

void
usage ( void )
{
	fprintf(stderr, "%s %s\n(c) Kied Llaentenn\n\n", argv0, VERSION);
	fprintf(stderr, "USAGE\n\turban < input.b > output.c\n");
	fprintf(stderr, "\nOPTIONS\n");
	fprintf(stderr, "\t-h\tshow this usage information.\n");
	fprintf(stderr, "\t-V\tshow version and exit.\n");
	fprintf(stderr, "\t-v\tenable verbose information.\n");
	fprintf(stderr, "\t-[1-3]\tenable stage [1-3] optimizations.\n");
	exit(1);
}

void
version ( void )
{
	fprintf(stderr, "%s v%s\n", argv0, VERSION);
	exit(0);
}
