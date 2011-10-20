#include <stdio.h>
#include <glut.h>

#include "config.h"
#include "display.h"


void drawLEDCube() {
  int x, y, z;

  // LEDs
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ledOnMaterial);
  for (z=-10; z<=10; z+=10) // Ebene
    for (y=-10; y<=10; y+=10) // Zeile
      for (x=-10; x<=10; x+=10) { // Spalte
        glPushMatrix();
        glTranslatef(x, y, z);
        glutSolidSphere(1.0, 16, 16);
        gluCylinder(quadric, 1.0, 1.0, 1.3, 16, 2);
        //glTranslatef(x, y, z+0.8);
        //gluCylinder(quadric, 1.3, 1.3, 0.2, 16, 2);
        //gluDisk(

        glPopMatrix();
      }

  // Wires
  for (y=-10; y<=10; y+=10)
    for (x=-10; x<=10; x+=10) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ((x == 0 || y == 0) ? innerWireMaterial : wireMaterial));

      // Front
      glBegin(GL_LINES);
        glVertex3f(x, y, -10);
        glVertex3f(x, y, 10);
      glEnd();

      // Side
      glBegin(GL_LINES);
        glVertex3f(-10, x, y);
        glVertex3f(10, x, y);
      glEnd();

      // Top
      glBegin(GL_LINES);
        glVertex3f(x, -10, y);
        glVertex3f(x, 10, y);
      glEnd();
    }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(ZOOM_LEVEL, WINDOW_WIDTH/WINDOW_HEIGHT, 1.0, 350.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(lookX, eyeAngle, lookZ, 0, 0, 0, 0, 1, 0);

  drawLEDCube();
  glutSwapBuffers();
}

