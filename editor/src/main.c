#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include "config.h"
#include "display.h"
#include "input.h"


// Materials
float ledOnMaterial[] = {0.0, 0.0, 1.0, 1.0};
float ledOffMaterial[] = {0.1, 0.1, 0.1, 0.0};
float wireMaterial[] = {0.7, 0.7, 0.7, 1.0};
float innerWireMaterial[] = {0.2, 0.2, 0.2, 0.3};

// Colors
float backgroundColor[] = {0.3, 0.3, 0.3, 0.4};

// Positions
float light0Pos[] = {70, 70, 70, 0.0};
float lookX = 0.0, lookZ = 0.0;
float eyePos = 0.0, eyeAngle = 45.0;
int ledOrientation = TOP_ORIENTATION;

// Objects
GLUquadricObj *quadric;

// LED data
int currentFrame[27] = {0};


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("CTHN LEDCube Editor v0.1");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboard_special);
  glutMouseFunc(mouse);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);

  // Lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, backgroundColor);

  glMatrixMode(GL_MODELVIEW);
  moveCameraPosition(0); // Init the Position


  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricDrawStyle(quadric, GLU_FILL);

  glutMainLoop();

  return 0;
}

