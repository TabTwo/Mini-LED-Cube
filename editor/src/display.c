#include <stdio.h>
#include <glut.h>

#include "config.h"
#include "display.h"


void drawLEDs(int orientation, int mode) {
  int x, y, z;
  int colorIndex = 0;

  if (orientation == TOP_ORIENTATION) {
    glRotatef(90, 2, 0, 0);
  }

  for (z=-10; z<=10; z+=10) // Ebene
    for (y=-10; y<=10; y+=10) // Zeile
      for (x=-10; x<=10; x+=10) { // Spalte
        if (mode == PICKING_MODE) {
          glColor3ub(0, 0, colorIndex*8);
          colorIndex++;
        } else {
          glMaterialfv(GL_FRONT, GL_AMBIENT, (z == 0 ? ledOnMaterial : ledOffMaterial));
        }

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
}

void drawWires() {
  int x, y;
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

void setScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(ZOOM_LEVEL, WINDOW_WIDTH/WINDOW_HEIGHT, 1.0, 350.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(lookX, eyeAngle, lookZ, 0, 0, 0, 0, 1, 0);
}

// OpenGL Display function
void display() {
  setScene();
  drawLEDs(TOP_ORIENTATION, RENDER_MODE);
  drawWires();
  glutSwapBuffers();
}

// Picking function
void displayPickingObjects() {
  setScene();
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);

  drawLEDs(TOP_ORIENTATION, PICKING_MODE);

  glEnable(GL_LIGHTING);
  glEnable(GL_DITHER);
}

