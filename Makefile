CC=clang
CFLAGS=-Wall -Werror -Wextra

all:	passgen.c
	$(CC) -o passgen passgen.c $(CFLAGS)

clean:	
	rm passgen
