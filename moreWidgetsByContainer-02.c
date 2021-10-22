/*
TRIAL OF GUI APP DEVELOPMENT #02, 2021/10/22

Project Start: 2021/10/17

Purpose: Get used to GitHub and GTK4.0

GTK4.0 Learning Resource:
https://github.com/ToshioCP/Gtk4-tutorial/blob/main/gfm/sec4.md

Basically, source code is from the resource above.
I comment on it to make it easier to uderstand or remind.

#01: Displays just a GUI window
#02: More widgets by the container widget

GtkWindow and GtkApplicationWindow can have only one child widget.
GtkBox, one of the container widget, enables two or more child
widgets usage.

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

// alters the string of a label of a button.
static void
click1_cb(GtkButton *btn, gpointer user_data)
{
	const gchar *s;
	
	// gets the address of a label of a button.
	s = gtk_button_get_label(btn);
	
	// whether the string of the label is "Hello." or not.
	if (g_strcmp0(s, "Hello.") == 0)
	{
		// sets the string for the label.
		gtk_button_set_label(btn, "Good-bye.");
	}
	else
	{
		gtk_button_set_label(btn, "Hello.");

	}

}

// closes specified window. 
static void
click2_cb(GtkButton *btn, gpointer user_data)
{
	GtkWindow *win = GTK_WINDOW(user_data);
	gtk_window_destroy(win);
}

static void
app_activate(GApplication *app, gpointer *user_data)
{
	GtkWidget *win;
	GtkWidget *box;	
	GtkWidget *btn1;
	GtkWidget *btn2;

	// Top-Level Window
	// One application can have two or more top-level windows.
	// If Two or more windows are instantiated, they can be shown separately.

	// creates GtkApplicatonWindow and connects it to GtkApplication.
	win = gtk_application_window_new(GTK_APPLICATION(app));


	// win is casted to GtkWindow.
	gtk_window_set_title(GTK_WINDOW(win), "pr4");
	gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);


	// GtkWindow and GtkApplicationWindow can have
	// only one child.
	// GtkBox, one of the container widget, enables
	// appending two or more widgets in itself.
	
	// arranges the children widget vertically.
	// 5 is the size between them.
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	// fills the box the children given the equal space.
	gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
	

	// makes box a child widget of the win.
	gtk_window_set_child(GTK_WINDOW(win), box);

	// creates a instance of the button widget.
	btn1 = gtk_button_new_with_label("Hello.");
	
	// When btn1 is activated, it emits a signal, "cliked".
	// then a signal handler function "click_cb1" is called.
	// "cb" means "call back".
	g_signal_connect(btn1, "clicked", G_CALLBACK(click1_cb), NULL);
	
	btn2 = gtk_button_new_with_label("quit");
	
	// passes the value of win to click2_cb. 
	g_signal_connect(btn2, "clicked", G_CALLBACK(click2_cb), win);

	// appends child widgets to the box.
	gtk_box_append(GTK_BOX(box), btn1);
	gtk_box_append(GTK_BOX(box), btn2);


	// exceptionally, top window need to be shown explicitly.
	gtk_widget_show(win); 

}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int	stat;
	
	// creats application instance.
	app	= gtk_application_new("com.gui-app-dev", G_APPLICATION_FLAGS_NONE);

	// app emits a signal, "activate", 
	// which the siganl handler function, also called callback, 
	// "app_activate" will receive it and be invoked.
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

	// runs app, which emits a signal, so the handler is invoked.
	stat = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return stat;
}
