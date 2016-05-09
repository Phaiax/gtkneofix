

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <gdk/gdk.h>
#include <gtk/gtk.h>


/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void hello( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("Hello World\n");
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return TRUE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}


static gint key_pressed( GtkWidget *widget,
                         GdkEvent  *event,
                        gpointer   callback_data )
{
    g_print("Button pressed: ");
    GdkEventType type = event->type;

    if (type == GDK_KEY_PRESS) {
        GdkEventKey* eventkey = (GdkEventKey*) event;
        /*struct GdkEventKey {
          GdkEventType type;
          GdkWindow *window;
          gint8 send_event;
          guint32 time;
          guint state;
          guint keyval;
          gint length;
          gchar *string;
          guint16 hardware_keycode;
          guint8 group;
          guint is_modifier : 1;
        };*/
          g_print("keyval %d, ", eventkey->keyval);
          g_print("send_event %d, ", eventkey->send_event);
          g_print("state %d, ", eventkey->state);
          g_print("length %d, ", eventkey->length);
          g_print("hwkc %d, ", eventkey->hardware_keycode);
          g_print("group %d, ", eventkey->group);
          g_print("is_modifier %d, ", eventkey->is_modifier);
          g_print(" => %s", eventkey->string);
    }

    g_print("\n");

}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;

    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
              G_CALLBACK (delete_event), NULL);

    /* Here we connect the "destroy" event to a signal handler.
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete-event" callback. */
    g_signal_connect (window, "destroy",
              G_CALLBACK (destroy), NULL);


    g_signal_connect(window, "key_press_event",
              G_CALLBACK (key_pressed), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Creates a new button with the label "Hello World". */
    button = gtk_button_new_with_label ("Hello World");

    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (button, "clicked",
              G_CALLBACK (hello), NULL);

    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
    g_signal_connect_swapped (button, "clicked",
                  G_CALLBACK (gtk_widget_destroy),
                              window);

    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), button);

    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);

    /* and the window */
    gtk_widget_show (window);

    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();

    return 0;
}