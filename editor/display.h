#ifndef _DISPLAY_H
#define _DISPLAY_H

// OpenGL Cube
void drawLEDs(gint mode);
void drawWires();

void display(gboolean onlyForPicking);

void setScene();

// Hardware Cube
void displayCurrentFrame();
void uploadAnimation();

#endif

