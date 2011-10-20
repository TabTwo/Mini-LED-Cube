#include <stdio.h>
#include <math.h>
#include <glut.h>

#include "config.h"
#include "input.h"

void moveCameraPosition(float direction) {
  eyePos += direction;
  if (eyePos > 360.0) eyePos = 0.0;

  lookX = sin(eyePos * PI/180.0)*70.0;
  lookZ = cos(eyePos * PI/180.0)*70.0;
}

void moveCameraAngle(float angle) {
  eyeAngle += angle;
  if (eyeAngle > 120) eyeAngle = 120;
  if (eyeAngle < 0) eyeAngle = 0;
}


void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // ESC
      exit(0);
      break;
  }
  glutPostRedisplay();
}

void keyboard_special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      moveCameraPosition(MOVE_SPEED);
      break;
    case GLUT_KEY_RIGHT:
      moveCameraPosition(MOVE_SPEED*-1);
      break;
    case GLUT_KEY_UP:
      moveCameraAngle(MOVE_SPEED);
      break;
    case GLUT_KEY_DOWN:
      moveCameraAngle(MOVE_SPEED*-1);
  }
  glutPostRedisplay();
}

