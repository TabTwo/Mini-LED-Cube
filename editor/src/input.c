#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/glut.h>

#include "config.h"
#include "input.h"
#include "display.h"


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

void mouse(int x, int y) {
  int position, viewport[4];
  GLubyte pixel[3];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)pixel);
  position = ((int)pixel[2]/8)-1; // Selected LED

  printf("%d\n", position);
  currentFrame[position] = currentFrame[position] == 0 ? 1 : 0;
  printf("%d\n", currentFrame[position]);
}

