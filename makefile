#
# urban: an optimizing Brainfsck compiler
# (c) Kied Llaentenn
# See the LICENSE for more information
#

# for those who lack clang/lld
#CC	= gcc
#CFLAGS	= -ggdb -std=c99 -pedantic -Os

CC	= clang
CFLAGS	= -g -std=c99 -pedantic -Os
LDFLAGS	= -fuse-ld=lld

SRC	= opt2.c main.c
OBJ	= $(SRC:.c=.o)

all: clean urban

clean:
	rm -f urban $(OBJ)

urban: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: all clean
