
Sublime NEO layout fix
======================

This is a gtk plugin that fixes [a problem](https://forum.sublimetext.com/t/neo-keyboard-layout-not-full-supported/4477/13) with the fourth layer of the NEO 2 keyboard layout with sublime. Sublime ignores the layer 4 mapped keys like Left, Right, Backspace, Enter, ... that can be accessed via MOD4 + S,F,W,V, ...

Usage
-----

Start sublime by prior setting the `GTK_MODULES` environment variable, so that this module is loaded.

`GTK_MODULES=gtkneofix-gtk-module:$GTK_MODULES sublime_text`

Debugging: If something does not work as expected, start sublime with `-w`. See output and [ask](https://github.com/Phaiax/gtkneofix/issues/new).

Installation
------------

Needed tools, libraries and compilers (If I forgot something, please issue a ticket):
```
    sudo apt-get install autoconf build-essential libgtk2.0-dev git libtool automake
```

Then execute these commands
```
    git clone https://github.com/Phaiax/gtkneofix.git
    cd gtkneofix
    autoreconf -i
    ./configure
    make
    sudo make install
    # revert
    sudo make uninstall
```

`make install` only creates these files (the final directory may differ between distributions)
```
└── usr
    └── lib
        └── x86_64-linux-gnu
            └── gtk-2.0
                └── modules
                    ├── libgtkneofix-gtk-module.a
                    ├── libgtkneofix-gtk-module.la
                    └── libgtkneofix-gtk-module.so
```


Note: Even if the configure script allows to set --with-gtk=3, it may not work for GTK3 apps. (Sublime uses GTK2)


Dev Notes
---------

It took some effort for me to find this method of fixing the problem, since I knew nothing about how keys were handled and nothing about GTK :D


This app can be used to test the keys.

./gtktestapp --gtk-module $PWD/.libs/libgtkneofix-gtk-module.so


Interesting pieces of code

```
gtk_main_do_events
    gtk_propagate_event ??

gdkevents.c
    gdk_event_handler_set // GTK does: gdk_event_handler_set(gtk_main_do_events)
                          // @ gtkmain.c:680 do_pre_parse_initialization():
                          // ...   gdk_event_handler_set ((GdkEventFunc)gtk_main_do_event, NULL, NULL);
                          // danach ist _gdk_event_func = gtk_main_do_event

gdkeventloop-quarz.c:672 gdk_event_dispatch calls _gdk_event_func
                                            with the event from _gdk_event_unqueue()
gdkevents-x11.c:2328 _gdk_events_queue() get events from X11 and append them to queue
               :1015,1141,661 translation from x events to gdk events,
                              calls gdk_keymap_translate_keyboard_state()

gtkdialog.c
    gtk_dialog_close // possibility to create own events and propagate them through the usual event handling

gtkwidget.c:4890
    gtk_widget_event_internal(): emits event auf widget
        emittet erst signal EVENT, dann das dem event entsprechende signal, dann das signal EVENT_AFTER
        das entsprechende signal wird nach event->type ausgesucht, zb event->type==GDK_KEY_PRESS
    gtk_widget_event(): calls gtk_widget_event_internal()
gtkwindow.c:5179
    gtk_window_propagate_key_event(): Propagate a key press or release event to the focus widget and
                                      up the focus container chain until a widget handles @event.
    gtk_window_key_press_event(): calls * gtk_window_activate_key
                                        * gtk_window_propagate_key_event
                                        * key_press_event
    fktptr window->key_press_event = gtk_window_key_press_event
gtkwidget.c:1381 // signal_new key-pressed
    signal key-press-event calls widget->key_press_event
```



