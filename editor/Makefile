CC = gcc-4.4
CFLAGS = -Wall
LINKER_FLAGS = -lglut -lGL -lGLU -export-dynamic
CFLAGS += `pkg-config --cflags --libs gtk+-2.0 gtkglext-1.0 libglade-2.0 gmodule-export-2.0`

CFLAGS += `libusb-config --cflags`
LINKER_FLAGS += `libusb-config --libs`

all:
	$(CC) $(CFLAGS) -c display.c
	$(CC) $(CFLAGS) -c input.c
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -c ../client/ledcube.c
	$(CC) $(CFLAGS) -c ../client/opendevice.c

	$(CC) $(CFLAGS) $(LINKER_FLAGS) -o ledcube-edit main.o display.o input.o ledcube.o opendevice.o
	chmod +x ledcube-edit
	#strip ledcube-edit

clean:
	rm -f *.o
	rm -f gui
	rm -f ledcube-edit
