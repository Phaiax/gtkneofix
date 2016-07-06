

#include <gdk/gdk.h>
#include <gtk/gtk.h>

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

static const gboolean DEBUG = TRUE;

static gint print_key ( GdkEvent  *event ) {

    if (event->type == GDK_KEY_PRESS || event->type == GDK_KEY_RELEASE) {
        GdkEventKey* eventkey = (GdkEventKey*) event;
        g_print("{ keyval %d, ", eventkey->keyval);
        g_print("send_event %d, ", eventkey->send_event);
        g_print("state %d, ", eventkey->state);
        g_print("length %d, ", eventkey->length);
        g_print("hwkc %d, ", eventkey->hardware_keycode);
        g_print("group %d, ", eventkey->group);
        g_print("is_modifier %d, ", eventkey->is_modifier);
        g_print(" => %s }", eventkey->string);
    }
}

static void magic(GdkEventKey *event) {

/*
ORIGINAL
 Right { keyval 65363, send_event 0, state 0, length 0, hwkc 114, group 0, is_modifier 0,  =>  }
 Left { keyval 65361, send_event 0, state 0, length 0, hwkc 113, group 0, is_modifier 0,  =>  }
 Up { keyval 65362, send_event 0, state 0, length 0, hwkc 111, group 0, is_modifier 0,  =>  }
 Down { keyval 65364, send_event 0, state 0, length 0, hwkc 116, group 0, is_modifier 0,  =>  }
 Backspace { keyval 65288, send_event 0, state 0, length 0, hwkc 22, group 0, is_modifier 0,  =>  }
 Enter  { keyval 65293, send_event 0, state 0, length 1, hwkc 36, group 0, is_modifier 0,  =>  }
 Delete { keyval 65535, send_event 0, state 0, length 0, hwkc 119, group 0, is_modifier 0,  =>  }
 Pos1 { keyval 65360, send_event 0, state 0, length 0, hwkc 110, group 0, is_modifier 0,  =>  }
 PageUp { keyval 65365, send_event 0, state 0, length 0, hwkc 112, group 0, is_modifier 0,  =>  }
 PageDown { keyval 65366, send_event 0, state 0, length 0, hwkc 117, group 0, is_modifier 0,  =>  }
 End { keyval 65367, send_event 0, state 0, length 0, hwkc 115, group 0, is_modifier 0,  =>  }
 Tab { keyval 65289, send_event 0, state 0, length 0, hwkc 23, group 0, is_modifier 0,  =>  }
 Esc { keyval 65307, send_event 0, state 0, length 1, hwkc 9, group 0, is_modifier 0,  =>  }
 Ins { keyval 65379, send_event 0, state 0, length 0, hwkc 118, group 0, is_modifier 0,  =>  }

NEO at LEVEL MOD4
 Right { keyval 65363, send_event 0, state 32, length 0, hwkc 41, group 0, is_modifier 0,  =>  }
 Left { keyval 65361, send_event 0, state 32, length 0, hwkc 39, group 0, is_modifier 0,  =>  }
 Up { keyval 65362, send_event 0, state 32, length 0, hwkc 26, group 0, is_modifier 0,  =>  }
 Down { keyval 65364, send_event 0, state 32, length 0, hwkc 40, group 0, is_modifier 0,  =>  }
 Backspace{ keyval 65288, send_event 0, state 32, length 0, hwkc 25, group 0, is_modifier 0,  =>  }
 Enter { keyval 65293, send_event 0, state 32, length 1, hwkc 55, group 0, is_modifier 0,  => }
 Delete{ keyval 65535, send_event 0, state 32, length 0, hwkc 27, group 0, is_modifier 0,  =>  }
 Pos1 { keyval 65360, send_event 0, state 32, length 0, hwkc 38, group 0, is_modifier 0,  =>  }
 PageUp { keyval 65365, send_event 0, state 32, length 0, hwkc 24, group 0, is_modifier 0,  =>  }
 PageDown{ keyval 65366, send_event 0, state 32, length 0, hwkc 28, group 0, is_modifier 0,  =>  }
 End { keyval 65367, send_event 0, state 32, length 0, hwkc 42, group 0, is_modifier 0,  =>  }
 Tab { keyval 65289, send_event 0, state 32, length 0, hwkc 53, group 0, is_modifier 0,  =>  }
 Esc { keyval 65307, send_event 0, state 32, length 1, hwkc 52, group 0, is_modifier 0,  =>  }
 Ins { keyval 65379, send_event 0, state 32, length 0, hwkc 54, group 0, is_modifier 0,  =>  }


 MOD4 { keyval 65041, send_event 0, state 0, length 0, hwkc 94, group 0, is_modifier 0,  =>  }




 It is neccessary to change state (clear MOD4 bit by -= 32)
                  and set the hardware_keycode to the correct value
*/

    if (event->state >= 32) { // MOD4

        // Right
        if(event->keyval == 65363 && event->hardware_keycode == 41) {
            event->hardware_keycode = 114;
            event->state -= 32; // remove MOD4
        }
        // Left
        else if(event->keyval == 65361 && event->hardware_keycode == 39) {
            event->hardware_keycode = 113;
            event->state -= 32;
        }
        // Up
        else if(event->keyval == 65362 && event->hardware_keycode == 26) {
            event->hardware_keycode = 111;
            event->state -= 32;
        }
        // Down
        else if(event->keyval == 65364 && event->hardware_keycode == 40) {
            event->hardware_keycode = 116;
            event->state -= 32;
        }
        // Backspace
        else if(event->keyval == 65288 && event->hardware_keycode == 25) {
            event->hardware_keycode = 22;
            event->state -= 32;
        }
        // Enter
        else if(event->keyval == 65293 && event->hardware_keycode == 55) {
            event->hardware_keycode = 36;
            event->state -= 32;
        }
        // Delete
        else if(event->keyval == 65535 && event->hardware_keycode == 27) {
            event->hardware_keycode = 119;
            event->state -= 32;
        }
        // Pos1
        else if(event->keyval == 65360 && event->hardware_keycode == 38) {
            event->hardware_keycode = 110;
            event->state -= 32;
        }
        // PageUp
        else if(event->keyval == 65365 && event->hardware_keycode == 24) {
            event->hardware_keycode = 112;
            event->state -= 32;
        }
        // PageDown
        else if(event->keyval == 65366 && event->hardware_keycode == 28) {
            event->hardware_keycode = 117;
            event->state -= 32;
        }
        // End
        else if(event->keyval == 65367 && event->hardware_keycode == 42) {
            event->hardware_keycode = 115;
            event->state -= 32;
        }
        // Tab
        else if(event->keyval == 65289 && event->hardware_keycode == 53) {
            event->hardware_keycode = 23;
            event->state -= 32;
        }
        // Esc
        else if(event->keyval == 65307 && event->hardware_keycode == 52) {
            event->hardware_keycode = 9;
            event->state -= 32;
        }
        // Ins
        else if(event->keyval == 65379 && event->hardware_keycode == 54) {
            event->hardware_keycode = 118;
            event->state -= 32;
        }
    }
}

gint keysnooper_cb (GtkWidget *grab_widget,
                    GdkEventKey *event,
                    gpointer func_data)
{
    if (DEBUG) {
        print_key( (GdkEvent*) event);
        g_print("\n");
    }

    magic(event);

    return FALSE; // further process event
}

G_MODULE_EXPORT void gtk_module_init (gint *argc, gchar ***argv)
{
    gtk_key_snooper_install(keysnooper_cb, NULL);
    g_print("SUBLIME NEO FIX GTK MODULE LOADED\n");
}
