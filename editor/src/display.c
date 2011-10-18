#include <stdio.h>
#include <glut.h>

#include "config.h"
#include "display.h"

extern void moveCameraPosition(float direction);

void drawLEDCube() {
  glMatrixMode(GL_MODELVIEW);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ledOnMaterial);

  int x, y, z;
  float space = 10.0;
  for (z=0; z<3; ++z) // Ebene
    for (y=0; y<3; ++y) // Zeile
      for (x=0; x<3; ++x) { // Spalte
        glPushMatrix();
        glTranslatef(x*space, y*space, z*space);
        glutSolidSphere(1.0, 16, 16);
        glPopMatrix();
      }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, WINDOW_WIDTH/WINDOW_HEIGHT, 1.0, 250.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  moveCameraPosition(0.0);
  gluLookAt(lookX, eyeAngle, lookZ, CUBE_SIZE/2, 6.0, CUBE_SIZE/2, 0, 1, 0);

  drawLEDCube();
  glutSwapBuffers();
}

