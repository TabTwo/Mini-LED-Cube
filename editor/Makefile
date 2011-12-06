CC=gcc
CFLAGS=-Wall
LINKER_FLAGS=-lglut -export-dynamic
GTKLIBS=`pkg-config --cflags --libs gtkglext-1.0 libglade-2.0 gmodule-export-2.0`
SRCDIR=src

all:
	$(CC) $(CFLAGS) $(GTKLIBS) -c $(SRCDIR)/display.c
	$(CC) $(CFLAGS) $(GTKLIBS) -c $(SRCDIR)/input.c
	$(CC) $(CFLAGS) $(GTKLIBS) -c $(SRCDIR)/event_callbacks.c
	$(CC) $(CFLAGS) $(GTKLIBS) -c $(SRCDIR)/main.c

	$(CC) $(CFLAGS) $(LINKER_FLAGS) $(GTKLIBS) -o ledcube-edit main.o display.o input.o
	chmod +x ledcube-edit
	#strip ledcube-edit

clean:
	rm -f *.o
	rm -f gui
	#rm -f ledcube-edit

