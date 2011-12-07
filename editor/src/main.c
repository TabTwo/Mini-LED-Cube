#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <glade/glade.h>

#include <GL/glut.h>

#include "config.h"
#include "display.h"
#include "input.h"
#include "event_callbacks.c"

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
GdkGLConfig *glConfig;
GdkGLContext *glContext;
GtkWidget *window, *drawingArea;

// LED data
int currentFrame[27] = {0};


int main(int argc, char *argv[]) {
  GladeXML *xml;

  gtk_init(&argc, &argv);
  gdk_gl_init(&argc, &argv);
  glutInit(&argc, argv);

  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricDrawStyle(quadric, GLU_FILL);

  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  moveCameraPosition(0);

  currentFrame[0] = 1; // TODO: remove

  // Configure the OpenGL widget
  glConfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE);
  if (glConfig == NULL) {
    g_print("EEE Double buffer not available, trying single buffer.");
    glConfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH);
    if (glConfig == NULL) {
      g_print("EEE Sorry, can't configure the OpenGL window. Giving up.");
      exit(1);
    }
  }

  xml = glade_xml_new("src/main_gui.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);

  window = glade_xml_get_widget(xml, "main_window");
  gtk_container_set_reallocate_redraws(GTK_CONTAINER(window), TRUE);
  drawingArea = glade_xml_get_widget(xml, "drawing_area");
  gtk_widget_set_gl_capability(drawingArea, glConfig, NULL, TRUE, GDK_GL_RGBA_TYPE);


  gtk_widget_show(window);
  gtk_main();

  return 0;
}

