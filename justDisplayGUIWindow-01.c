/*
TRIAL OF GUI APP DEVELOPMENT #01, 2021/10/17

Start: 2021/10/17

Purpose: Get used to GitHub and GTK4.0

#01: Displays just a GUI window
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


// preparation for the later 
// maybe this program will be GUI to-do-list app 
typedef struct TASK 
{
	int		id;	
	int		time;
	char	todo[64];
	void	*next;
} task;

static void
app_activate(GApplication *app, gpointer *user_data)
{
	GtkWidget *win;

	// creates GtkApplicatonWindow and connects it to GtkApplication
	win = gtk_application_window_new(GTK_APPLICATION(app));

	// win is casted to GtkWindow
	gtk_window_set_title(GTK_WINDOW(win), "pr4");
	gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);
	
	// eceptionally, top window need to be shown explicitly
	gtk_widget_show(win); 
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int	stat;
	
	// creats application instance
	app	= gtk_application_new("com.gui-app-dev", G_APPLICATION_FLAGS_NONE);

	// app emits a signal, "activate", 
	// which the siganl handler, also called callback, 
	// function "app_activate" will receive it and be invoked
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

	// runs app, which emits a signal, so the handler is invoked
	stat = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return stat;
}
