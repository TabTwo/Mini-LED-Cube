#include <gtk/gtk.h>

void on_window_destroy(GtkObject *object, gpointer userData) {
  gtk_main_quit();
}

int main (int argc, char *argv[]) {
  GtkBuilder *builder;
  GtkWidget *window;

  gtk_set_locale();
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "src/main_gui.ui", NULL);
  gtk_builder_connect_signals(builder, NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

  g_object_unref(G_OBJECT(builder));

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

