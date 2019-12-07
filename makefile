CC	= gcc
CFLAGS	= -ggdb -std=c99 -pedantic -O3

SRC	= main.c
OBJ	= $(SRC:.c=.o)

all: clean urban

clean:
	rm -f urban $(OBJ)

urban: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all clean
