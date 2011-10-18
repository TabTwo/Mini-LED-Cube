CC=gcc
CFLAGS=-Wall
INCLUDES=-I/usr/include/GL
LIBS=-lglut -lGLU -lGL -lm

SRCDIR=src

all:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/display.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/input.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/main.c

	$(CC) $(CFLAGS) $(LIBS) -o ledcube-edit main.o display.o input.o
	chmod +x ledcube-edit

clean:
	rm -f *.o
	#rm -f ledcube-edit

