
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include "config.h"
#include "display.h"
#include "input.h"

float ledOnMaterial[] = {1.0, 0.0, 0.0, 1.0};

float lookX = 0.0, lookZ = 0.0;
float eyePos = 0.0, eyeAngle = 50.0;

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

  glMatrixMode(GL_MODELVIEW);
  glutMainLoop();

  return 0;
}

