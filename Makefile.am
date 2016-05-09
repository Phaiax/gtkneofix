
ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

noinst_PROGRAMS = gtktestapp
gtktestapp_SOURCES = src/gtk_test_app.c
gtktestapp_CPPFLAGS = $(GTK_CFLAGS)
gtktestapp_LDADD = $(GTK_LIBS)


gtkmoduledir = @GTK_MODULE_DIR@
gtkmodule_LTLIBRARIES = libgtkneofix-gtk-module.la

libgtkneofix_gtk_module_la_SOURCES = src/gtk_module.c
libgtkneofix_gtk_module_la_CFLAGS = $(GTK_CFLAGS)
libgtkneofix_gtk_module_la_LIBADD = $(GTK_LIBS)
libgtkneofix_gtk_module_la_LDFLAGS = -avoid-version -module -export-dynamic


