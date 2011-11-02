#ifndef _INPUT_H
#define _INPUT_H

void moveCameraPosition(float direction);
void moveCameraAngle(float angle);

void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);

void mouse(int button, int state, int x, int y);

#endif

