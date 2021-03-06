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
GladeXML *xml;

// LED data
gint animation[32][28] = {{0}};
gint currentFrame = 0;
gint animationLength = 1;

// Hardware
gboolean isCubeConnected = FALSE;


void connectToLEDCube(void) {
  char message[255];
  int ret = 0;
  int attempts = 0;
  GtkLabel *statusLine = GTK_LABEL(glade_xml_get_widget(xml, "connection_label"));

  // We wait till the User connects the cube
  while (ret == 0 || ret != SUCCESSFULLY_CONNECTED) {
    attempts++;
    sprintf(message, "Try to detect the LED-Cube ... %d", attempts);
    gtk_label_set_text(statusLine, message);
    ret = lc_init();
    if (ret == SUCCESSFULLY_CONNECTED) {
      displayCurrentFrame();
      break;
    }
    sleep(2);
  }
  isCubeConnected = TRUE;
  gtk_label_set_text(statusLine, "LED-Cube successfully connected!");

  //TODO: Start the watchdog
}

gint main(gint argc, gchar *argv[]) {
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

  // Configure the first frame
  animation[currentFrame][13] = 1;
  animation[currentFrame][27] = 1; // delay to "normal"
  g_print("frame: %d\n", currentFrame);
  gtk_combo_box_set_active(GTK_COMBO_BOX(glade_xml_get_widget(xml, "dropdown_delay")), 1);
  moveCameraPosition(21);


  glade_xml_signal_autoconnect(xml);

  if (g_thread_supported()) {
    g_thread_init(NULL);
    gdk_threads_init();
  } else {
    g_error("Threads not supported, we die.");
    exit(1);
  }

  // Start the polling thread to try to connect to the LED-Cube.
  GError *error;
  g_thread_init(NULL);
  connectThread = g_thread_create((GThreadFunc)connectToLEDCube, NULL, TRUE, &error);
  if (connectThread == NULL) {
    g_error("Can't create the thread, we stop here.");
    exit(1);
  }

  gtk_widget_show(window);
  gtk_main();

  lc_close();
  return 0;
}

