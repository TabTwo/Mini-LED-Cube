#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/glut.h>

#include "config.h"
#include "input.h"
#include "display.h"

#include "../firmware/globals.h"   /* custom request numbers */

extern void lc_init(void);

void moveCameraPosition(gfloat direction) {
  eyePos += direction;
  if (eyePos > 360.0) eyePos = 0.0;

  lookX = sin(eyePos * M_PI/180.0)*70.0;
  lookZ = cos(eyePos * M_PI/180.0)*70.0;
}

void moveCameraAngle(gfloat angle) {
  eyeAngle += angle;
  if (eyeAngle > 120) eyeAngle = 120;
  if (eyeAngle < 0) eyeAngle = 0;
}

void mouse(gint x, gint y) {
  gint position, viewport[4];
  GLubyte pixel[3];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)pixel);
  position = ((gint)pixel[2]/8)-1; // Selected LED

  printf("%d\n", position);
  currentFrame[position] = currentFrame[position] == 0 ? 1 : 0;
  printf("%d\n", currentFrame[position]);
}

