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
gfloat ledOnMaterial[] = {0.0, 0.0, 1.0, 0.4};
gfloat ledOffMaterial[] = {0.1, 0.1, 0.1, 0.0};
gfloat wireMaterial[] = {0.7, 0.7, 0.7, 1.0};
gfloat innerWireMaterial[] = {0.3, 0.3, 0.3, 0.3};

// Colors
gfloat backgroundColor[] = {0.3, 0.3, 0.3, 0.4};

// Positions
gfloat light0Pos[] = {70, 70, 70, 0.0};
gfloat lookX = 0.0, lookZ = 0.0;
gfloat eyePos = 0.0, eyeAngle = 45.0;
gint ledOrientation = TOP_ORIENTATION;

// Objects
GLUquadricObj *quadric;
GdkGLConfig *glConfig;
GdkGLContext *glContext;
GtkWidget *window, *drawingArea;

// LED data
gint currentFrame[27] = {0};


void* connectToLEDCube(void) {
  int ret = NULL;
  while (ret == NULL || ret != SUCCESSFULLY_CONNECTED) {
    ret = lc_init();
    g_print("connecting ...");
    sleep(3);
  }
}

gint main(gint argc, gchar *argv[]) {
  GladeXML *xml;
  GThread *connectThread;

  gtk_init(&argc, &argv);
  gdk_gl_init(&argc, &argv);
  glutInit(&argc, argv);

  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricDrawStyle(quadric, GLU_FILL);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, backgroundColor);

  glMatrixMode(GL_MODELVIEW);
  moveCameraPosition(0);

  // Configure the OpenGL widget
  glConfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH | GDK_GL_MODE_DOUBLE);
  if (glConfig == NULL) {
    g_warning("Double buffer not available, trying single buffer.");
    glConfig = gdk_gl_config_new_by_mode(GDK_GL_MODE_RGB | GDK_GL_MODE_DEPTH);
    if (glConfig == NULL) {
      g_error("Sorry, can't configure the OpenGL window. Giving up.");
      exit(1);
    }
  }

  xml = glade_xml_new("main_gui.glade", NULL, NULL);

  window = glade_xml_get_widget(xml, "main_window");
  gtk_container_set_reallocate_redraws(GTK_CONTAINER(window), TRUE);
  drawingArea = glade_xml_get_widget(xml, "drawing_area");
  gtk_widget_set_gl_capability(drawingArea, glConfig, NULL, TRUE, GDK_GL_RGBA_TYPE);

  glade_xml_signal_autoconnect(xml);

  if (g_thread_supported()) {
    g_print("1");
    g_thread_init(NULL);
    g_print("2");
    gdk_threads_init();
    g_print("3");
  } else {
    g_error("Threads not supported, we die.");
    exit(1);
  }

  GError *error;

  g_thread_init(NULL);
  if (connectThread = g_thread_create((GThreadFunc)connectToLEDCube, NULL, TRUE, &error) == NULL) {
    g_error("Can't create the thread, we stop here.");
    exit(1);
  }
  //g_thread_join(connectThread);

  gtk_widget_show(window);
  gtk_main();

  lc_close();
  return 0;
}

