CC = gcc
CFLAGS = -Wall -g -c

all: program

program: src/main.o src/addon.o src/options.o 
	$(CC) -g -o styre src/main.o src/addon.o src/options.o

src/addon.o: src/addon.c
	$(CC) $(CFLAGS) -o src/addon.o src/addon.c

src/options.o: src/options.c
	$(CC) $(CFLAGS) -o src/options.o src/options.c

src/main.o: src/main.c
	$(CC) $(CFLAGS) -o src/main.o src/main.c

clean:
	rm -f src/*.o
