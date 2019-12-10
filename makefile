#
# urban: an optimizing Brainfsck compiler
# (c) Kied Llaentenn
# See the LICENSE for more information
#

# for those who lack clang/lld
#CC	= gcc
#CFLAGS	= -ggdb -std=c99 -pedantic -Os

WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Werror

CC	= clang
CFLAGS	= -g -std=c99 $(WARNING)
LDFLAGS	= -fuse-ld=lld

SRC	= opt2.c opt3.c assm.c emit.c main.c
OBJ	= $(SRC:.c=.o)

all: urban

clean:
	rm -f urban $(OBJ)

urban: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: all clean
