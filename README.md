gtk_main_do_events
    gtk_propagate_event ??



gdkevents.c
    gdk_event_handler_set // GTK does: gdk_event_handler_set(gtk_main_do_events)
                          // @ gtkmain.c:680 do_pre_parse_initialization():
                          // ...   gdk_event_handler_set ((GdkEventFunc)gtk_main_do_event, NULL, NULL);


gtkdialog.c
    gtk_dialog_close // possibility to create own events and propagate them through the usual event handling



STEPS:
    mkdir -p ~/tmp/sublpatch
    cd ~/tmp/sublpatch
    apt-get source libgtk2.0-0
    sudo apt-get build-dep libgtk2.0-0
    cd gtk+2.0-*
    ./configure
    make


    gtkmain.c:1054 gtk_init()

    LD_LIBRARY_PATH=/home/daniel/tmp/gtk/gtk+2.0-2.24.23/gtk/.libs:$LD_LIBRARY_PATH  GTK_PATH=/usr/lib/x86_64-linux-gnu/gtk-2.0 sublime_text -w


./gtktestapp --gtk-module $PWD/.libs/libgtkneofix-gtk-module.so