
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include "config.h"
#include "display.h"
#include "input.h"

float ledOnMaterial[] = {0.0, 0.0, 1.0, 1.0};
float wireMaterial[] = {0.7, 0.7, 0.7, 1.0};
float innerWireMaterial[] = {0.2, 0.2, 0.2, 0.3};

float light_diffuse[] = {0.0, 0.0, 1.0, 1.0};
float light_position[] = {1.0, 1.0, 1.0, 0.0};


float lookX = 0.0, lookZ = 0.0;
float eyePos = 0.0, eyeAngle = 45.0;

GLUquadricObj *quadric;

extern void moveCameraPosition(float direction);

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("CTHN LEDCube Editor");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboard_special);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);

  // OpenGL Features
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  moveCameraPosition(0); // Init the Position


  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricDrawStyle(quadric, GLU_FILL);

  glutMainLoop();

  return 0;
}

