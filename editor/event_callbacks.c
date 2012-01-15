#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/glut.h>
#include <gdk/gdkkeysyms.h>

#include <stdio.h>

#include "../firmware/globals.h"

#include "config.h"
#include "input.h"
#include "display.h"

extern int lc_setFrame(unsigned long);
extern int lc_setMode(int);
extern int lc_saveFrame(unsigned long, int, int);
extern int lc_init(void);
extern int lc_close(void);


// "Live" Mode. If a user clicks a LED, the frame needs to re-send to
// the LEDCube.
void on_change_led() {
  int success = lc_init();
  if (success == SUCCESSFULLY_CONNECTED) {
    // Reorder the frame array to a 32bit int?
    unsigned long frame = 0;
    gint i = 0;
    for (i=0; i<27; ++i) {
      frame |= (animation[currentFrame][i] << i);
    }

    // Send it to the cube
    lc_setFrame(frame);
  }
}

// TODO: Make it work on the GUI (button etc.)
void on_change_mode(int newMode) {
  lc_setMode(newMode);
}

gchar* on_frame_control_format_value(GtkScale *scale, gdouble value) {
  return g_strdup_printf("%d/%d", (int)value, animationLength);
}

void on_frame_control_value_changed(GtkRange *frameControl) {
  currentFrame = (int)(gtk_range_get_value(frameControl)-1);
  g_print("frame: %d\n", currentFrame);
  gtk_widget_queue_draw_area(drawingArea, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  displayCurrentFrame();
}

void on_button_add_clicked(GtkButton *button) {
  if (animationLength >= 32) return;
  
  GtkRange *frameControl = GTK_RANGE(glade_xml_get_widget(xml, "frame_control"));

  animationLength++;
  currentFrame = animationLength-1;
  gtk_range_set_range(frameControl, 1.0, (double)animationLength+1.0);
  gtk_range_set_value(frameControl, animationLength);

  gtk_widget_queue_draw_area(drawingArea, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  displayCurrentFrame();
}

void on_button_upload_clicked(GtkButton *button) {
  uploadAnimation();
}

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

