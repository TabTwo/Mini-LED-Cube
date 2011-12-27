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

gboolean on_drawing_area_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
  GdkGLContext *glContext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *glDrawable = gtk_widget_get_gl_drawable(widget);

  if (!gdk_gl_drawable_gl_begin(glDrawable, glContext)) return FALSE;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  display(FALSE);

  if (gdk_gl_drawable_is_double_buffered(glDrawable))
    gdk_gl_drawable_swap_buffers(glDrawable);
  else
    glFlush();
  gdk_gl_drawable_gl_end(glDrawable);

  return FALSE;
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

void on_drawing_area_button_press_event(GtkWidget *widget, gpointer data) {
  gtk_widget_grab_focus(widget);

  GdkGLContext *glContext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *glDrawable = gtk_widget_get_gl_drawable(widget);
  gint x, y;

  gtk_widget_get_pointer(widget, &x, &y);

  if (!gdk_gl_drawable_gl_begin(glDrawable, glContext)) return;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  display(TRUE);
  mouse(x, y);

  gdk_gl_drawable_gl_end(glDrawable);
  gtk_widget_queue_draw_area(widget, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

