
# This is David A. Wheeler's template for configure.ac, showing
# some suggested options and setups.

# Process this file with autoconf to produce a configure script.

# Initialize autoconf.
AC_INIT([gtkneofix], [0.01], [https://github.com/Phaiax/gtkneofix/issues], [gtkneofix], [https://github.com/Phaiax/gtkneofix])

AC_SUBST(LIBGTKNEOFIX_GTK_VERSION_INFO, [1:9:1])


# Force autoconf to be at least this version number:
AC_PREREQ([2.68])

# Safety check - list a source file that wouldn't be in other directories:
AC_CONFIG_SRCDIR([src/gtk_module.c])
# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])
# Put autotools auxiliary files in subdirectories to reduce clutter:
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Enable "automake" to simplify creating makefiles:
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])
AC_CONFIG_FILES([Makefile])

# Checks for programs, e.g., AC_PROG_CC
AC_PROG_CC
AC_PROG_CXX

AC_PROG_MKDIR_P
AC_PROG_LN_S
AM_PROG_AR
AC_PROG_LIBTOOL
AC_PROG_INSTALL


# Checks for libraries.

LT_PREREQ(2.2)
LT_INIT([dlopen win32-dll disable-static])


### GTK (optional) ####

AC_ARG_WITH([gtk], [AS_HELP_STRING([--with-gtk=2|3], [GTK+ version [default=2]])], [], [with_gtk=2])
AC_ARG_WITH([gtk-libdir], [AS_HELP_STRING([--with-gtk-libdir=DIR], [GTK+ library directory [default=`pkg-config --variable=libdir gtk+-3.0`]])], [], [with_gtk_libdir=`pkg-config --variable=libdir gtk+-\$with_gtk.0`])
AC_ARG_WITH([gtk-module-dir], [AS_HELP_STRING([--with-gtk-module-dir=DIR], [GTK+ module directory [default=`pkg-config --variable=libdir gtk+-3.0`/gtk-3.0/modules]])], [], [with_gtk_module_dir=$with_gtk_libdir/gtk-$with_gtk.0/modules])


AC_SUBST([GTK_VERSION], [$with_gtk])
AC_SUBST([GTK_MODULE_DIR], [$with_gtk_module_dir])

AM_CONDITIONAL([GTK3], [test GTK$with_gtk = GTK3])

PKG_CHECK_MODULES([GTK], [gtk+-$with_gtk.0])
AC_SUBST([GTK_CFLAGS])
AC_SUBST([GTK_LIBS])


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Do final output.
AC_OUTPUT
