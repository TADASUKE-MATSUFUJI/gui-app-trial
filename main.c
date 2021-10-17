/*
TRIAL OF GUI APP DEVELOPMENT

Start: 2021/10/17

Purpose: Get used to GitHub and GTK4.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
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

	g_print("GtkApplication is activated.\n");
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int	stat;

	app	= gtk_application_new("com.gui-app-dev", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
	stat = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref (app);
	return stat;
}
