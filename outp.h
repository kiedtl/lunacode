#ifndef OUTP_INCLUDED
#define OUTP_INCLUDED
#include "args.h"

extern struct Options *opts;

#define VERBOSE(...)	if (opts->verbose)\
				fprintf(stderr, __VA_ARGS__);

#endif
