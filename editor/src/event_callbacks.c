#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/glut.h>
#include <gdk/gdkkeysyms.h>

#include "config.h"
#include "input.h"
#include "display.h"

void on_main_window_delete_event(GtkObject *object, gpointer userData) {
  gtk_main_quit();
}

gboolean on_drawing_area_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
  GdkGLContext *glContext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *glDrawable =gtk_widget_get_gl_drawable(widget);

  if (!gdk_gl_drawable_gl_begin(glDrawable, glContext)) return FALSE;

  setScene();

  gdk_gl_drawable_gl_end(glDrawable);
  return FALSE;
}

gboolean on_drawing_area_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
  GdkGLContext *glContext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *glDrawable =gtk_widget_get_gl_drawable(widget);

  if (!gdk_gl_drawable_gl_begin(glDrawable, glContext)) return FALSE;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  display();

  if (gdk_gl_drawable_is_double_buffered(glDrawable))
    gdk_gl_drawable_swap_buffers(glDrawable);
  else
    glFlush();
  gdk_gl_drawable_gl_end(glDrawable);
  return FALSE;
}

void on_drawing_area_realize(GtkWidget *widget, gpointer data) {
  GdkGLContext *glContext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *glDrawable =gtk_widget_get_gl_drawable(widget);
  if (!gdk_gl_drawable_gl_begin(glDrawable, glContext)) return;

  gdk_gl_drawable_gl_end(glDrawable);
}

void on_drawing_area_key_press_event(GtkWidget *widget, GdkEventKey *event) {
  switch (event->keyval) {
    case GDK_KEY_Left:
      moveCameraPosition(MOVE_SPEED);
      break;
    case GDK_KEY_Right:
      moveCameraPosition(MOVE_SPEED*-1);
      break;
    case GDK_KEY_Up:
      moveCameraAngle(MOVE_SPEED);
      break;
    case GDK_KEY_Down:
      moveCameraAngle(MOVE_SPEED*-1);
      break;
  }

  gtk_widget_queue_draw_area(widget, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

