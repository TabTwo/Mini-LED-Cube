#include <stdio.h>
#include <glut.h>

#include "config.h"
#include "display.h"


void drawLEDCube(orientation) {
  int x, y, z;

  if (orientation == TOP_ORIENTATION) {
    glRotatef(90, 2, 0, 0);
  }

  // LEDs
  glMaterialfv(GL_FRONT, GL_AMBIENT, ledOnMaterial);
  for (z=-10; z<=10; z+=10) // Ebene
    for (y=-10; y<=10; y+=10) // Zeile
      for (x=-10; x<=10; x+=10) { // Spalte

        // TODO: Test different colors
        glMaterialfv(GL_FRONT, GL_AMBIENT, (z == 0 ? ledOnMaterial : ledOffMaterial));

        glPushMatrix();
        glTranslatef(x, y, z-0.8);
        glutSolidSphere(1, 16, 16);
        gluCylinder(quadric, 1, 1, 1.9, 16, 2);

        glTranslatef(0, 0, 1.9);
        gluCylinder(quadric, 1.25, 1.25, 0.35, 16, 2);

        gluDisk(quadric, 0, 1.25, 16, 16);
        glTranslatef(0, 0, 0.35);
        gluDisk(quadric, 0, 1.25, 16, 16);

        glPopMatrix();
      }

  // Wires
  for (y=-10; y<=10; y+=10)
    for (x=-10; x<=10; x+=10) {
      glMaterialfv(GL_FRONT, GL_AMBIENT, ((x == 0 || y == 0) ? innerWireMaterial : wireMaterial));

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

  drawLEDCube(TOP_ORIENTATION);
  glutSwapBuffers();
}

