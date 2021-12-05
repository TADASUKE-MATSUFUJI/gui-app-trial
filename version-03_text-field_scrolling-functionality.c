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
	
#03: Multi-line text edit field and Scrolling functionality 
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Preparation for the later 
// Maybe this program will be GUI to-do-list app 
typedef struct TASK 
{
	int		id;	
	int		time;
	char	todo[64];
	void	*next;
} task;

// Alters the string of a label of a button.
static void
click1_cb(GtkButton *btn, gpointer user_data)
{
	// Pointer to a constant:
	// Can not change the value the pointer points to through dereferencing.
	const gchar *s;
	
	// Gets the address of a label of a button.
	s = gtk_button_get_label(btn);
	
	// Whether the string of the label is "Hello." or not.
	if (g_strcmp0(s, "Hello.") == 0)
	{
		// Sets the string for the label.
		gtk_button_set_label(btn, "Good-bye.");
	}
	else
	{
		gtk_button_set_label(btn, "Hello.");

	}

}

// Closes specified window. 
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
	GtkWidget *src;
	GtkWidget *tv;
	GtkTextBuffer *tb;
	gchar *text;

	text =
"This code is to learn GTK.\n"
"I have not ever made GUI apps.\n" 
"I want to make first one!"
;

	// Top-Level Window
	// One application can have two or more top-level windows.
	// If two or more windows are instantiated, they can be shown separately.

	// Creates GtkApplicatonWindow and connects it to GtkApplication.
	win = gtk_application_window_new(GTK_APPLICATION(app));


	// Win is casted to GtkWindow.
	gtk_window_set_title(GTK_WINDOW(win), "GTK Challenge");
	gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);


	// GtkWindow and GtkApplicationWindow can have
	// only one child.
	// GtkBox, one of the container widget, 
	// enables appending two or more widgets in itself.

	// Arranges the children widget vertically.
	// 5 is the size between them.
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

	// Fills the box the children given the equal space.
	gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
	

	// Makes box a child widget of the win.
	gtk_window_set_child(GTK_WINDOW(win), box);

	// Creates a instance of the button widget.
	btn1 = gtk_button_new_with_label("Hello.");
	
	// When btn1 is activated, it emits a signal, "cliked".
	// Then a signal handler function "click_cb1" is called.
	// "cb" means "call back".
	g_signal_connect(btn1, "clicked", G_CALLBACK(click1_cb), NULL);
	
	btn2 = gtk_button_new_with_label("quit");
	
	// Passes the value of win to click2_cb. 
	g_signal_connect(btn2, "clicked", G_CALLBACK(click2_cb), win);

// GtkScrolledWindow enables scrolling functionality.
// Suppose what you views long web page.
// You can scroll on the page with the bar on the side of a window.

	// Creats GtkScrolledWindow instance,
	// then assign it address to src.
	src = gtk_scrolled_window_new();


	// Creats a GtkTextView instance,
	// then tv, a pointer, is assigned the instance's address.
	tv = gtk_text_view_new();

	// Creating a GtkTextView instance,
	// GtkTextBuffer instance is also created
	// and connected to the GtkTextView.
	// They are done automaically.

	// Gets the address of the GtkTextBuffer,
	// then assigns it to tb.
	tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));

	// Sets prepared texts to the buffer. 
	gtk_text_buffer_set_text(tb, text, -1);

	// Wrap mode:
	//   The line below sets the wrap mode to GTK_WRAP_WORD_CHAR.
	//   It wraps text in between words.
	//   It can do so between graphemes, too.
	//   I have not understood effects of them, yet.
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);


// GtkWindow and GtkApplicationWindow can have only one child.

	// Appends child widgets to the box.
	gtk_box_append(GTK_BOX(box), btn1);
	gtk_box_append(GTK_BOX(box), btn2);
	gtk_box_append(GTK_BOX(box), src);
	
	// Insert a GtkTextView to a GtkScrolledWindow as a child.
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(src), tv);

	// Exceptionally, top window need to be shown explicitly.
	gtk_widget_show(win); 

}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int	stat;
	
	// Creats application instance.
	app	= gtk_application_new("com.gui-app-dev", G_APPLICATION_FLAGS_NONE);

	// App emits a signal, "activate", 
	// which the siganl handler function, also called callback, 
	// "app_activate" will receive it and be invoked.
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

	// Runs app, which emits a signal, so the handler is invoked.
	stat = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return stat;
}
