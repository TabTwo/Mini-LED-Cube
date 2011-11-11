CC=gcc
CFLAGS=-Wall
INCLUDES=-I/usr/include/GL
LIBS=-lglut -lGLU -lGL -lm
GTKLIBS=`pkg-config --cflags --libs gtk+-2.0` -export-dynamic

SRCDIR=src

all:
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/display.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/input.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/main.c

	$(CC) $(CFLAGS) $(LIBS) -o ledcube-edit main.o display.o input.o
	chmod +x ledcube-edit
	strip ledcube-edit

gui:
	$(CC) $(CFLAGS) $(GTKLIBS) -o gui $(SRCDIR)/main_gui.c

clean:
	rm -f *.o
	rm -f gui
	#rm -f ledcube-edit

