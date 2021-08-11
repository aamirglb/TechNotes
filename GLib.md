# GLib

* Glib is a set of libraries, `GLib core`, `GObject` and `GIO`.

* GLib core provides data structure handling for C (linked lists, trees, hash tables,. . . ), portability wrappers, an event loop, threads, dynamic loading of modulesand lots of utility functions.

* GObject – which depends on GLib core – simplifies the object-oriented pro-gramming and event-driven programming paradigms in C. 

* GIO – which depends on GLib core and GObject – provides high-level APIs forinput/output: reading a local file, a remote file, a network stream, inter-processcommunication with D-Bus, and many more.

* GTK+ is a widget toolkit based on GLib that can be used to develop applicationswith a graphical user interface (GUI). 

* The first version of GTK+, or the GIMP Tool Kit4, was mainly written byPeter Mattis in 1996 for the GIMP (GNU Image Manipulation Program), buthas quickly become a general-purpose library.

*   GLib started as part of GTK+, but is now a standalonelibrary.

* An important project for GLib and GTK+ is GNOME (GNU Network Object Model Environment). GNOME, which is alsopart of GNU, is a free/libre desktop environment started in 1997 by Miguel de Icazaand Federico Mena-Quintero. GNOME makes extensive use of GTK+

*  Oldversions of GNOME included an object embedding architecture called Bonobo,and GNOME 1.0 included a fast, light CORBA ORB called ORBit. Bonobo hasbeen replaced by D-Bus, an inter-process communication system.

* Object-Oriented Design Heuristics, by Arthur Riel 
  The Algorithm DesignManual, by Steven Skiena 
 UNIX for the Impatient, by Paul Abrahams 
 Pro Git, by Scott Chacon

 * Thanks to GObject Introspection, automatic bindings are available for avariety of languages for all libraries based on GObject. Official GNOME bindingsare available for the following languages: C++, JavaScript, Perl, Python andVala7. Vala is a new programming language based on GObject which integratesthe peculiarities of GObject directly in its C#-like syntax. 

 * Each frontend should be a _"view"_ and a _"controller”_. As a “view,” the frontendmust note any changes in the backend, and change the display accordingly. Asa “controller,” the frontend must allow the user to relay requests for change tothe backend.

 * `sudo apt-get install libgtk2.0-dev`

 * GLib has a few toplevel headers:

 ```c
 glib.h // the main header
 gmodule.h // for dynamic loading of modules
 glib-unix.h // for Unix-specific APIs
 glib/gi18n.h and glib/gi18n-lib.h //for internationalization
 glib/gprintf.h and glib/gstdio.h //to avoid pulling in all of stdio.

 gint8, 
 guint8,
 gint16,
 guint16,
 gint32,
 guint32,
 gint64,
 guint64
 gboolean
 gchar
 gshort
 glong
 gint
 gfloat
 gdouble
 ```

 * `gpointer` may be more convenient to type than `void*`. `gconstpointer` gives you `const void*`.

 * `gsize` is an unsigned integer type that can hold the result of the sizeof operator.

 * `CLAMP(x, low, high)` means x, unless x is outside the range [low,high]; if x is below the range,low is returned; if x is above the range,high is returned.

 ```c
 #include<glib.h>

 GINT_TO_POINTER (p);
 GPOINTER_TO_INT (p);
 GUINT_TO_POINTER (p);
 GPOINTER_TO_UINT (p);
 ```

 ```c
 #include<glib.h>

 g_return_if_fail (condition);
 g_return_val_if_fail (condition, return_value);
 ```

 ```c
 gint my_int;
 gpointer my_pointer;
 my_int = 5;
 
 my_pointer = GINT_TO_POINTER (my_int);
 printf ("We are storing %d\n", GPOINTER_TO_INT (my_pointer));
 ```

 * GLib has a nice set of macros you can use to enforce _invariants_ and _pre-conditions_ in your code.  They all disappear when you define `G_DISABLE_CHECKS` or `G_DISABLE_ASSERT`, so there’s no performance penalty in production code.

 ```c
 #include<glib.h>
 g_assert (condition);
 g_assert_not_reached ();
 ```

 * `g_return_if_fail()` prints a warning and immediately returns from the current function if condition is `FALSE`. `g_return_val_if_fail()` is similar but allows you to return some return_value.

 * All of the debugging macros print a warning using GLib’s `g_log()` facility, whichmeans the warning includes the name of the originating application or library,and you can optionally install a replacement warning-printing routine.

 ```c
 include<glib.h>
 gpointer g_malloc (gsize n_bytes);
 void g_free (gpointer mem);
 gpointer g_realloc (gpointer mem, gsize n_bytes);
 gpointer g_memdup (gconstpointer mem, guint n_bytes);
 ```

 ```c
 gint g_snprintf (gchar *string, gulong n, gcharconst*format, ...);
 ```

 ```c
 // Allocating String
 #include<glib.h>
 gchar * g_strdup (constgchar *str);
 gchar * g_strndup (constgchar *str, gsize n);
 gchar * g_strdup_printf (constgchar *format, ...);
 gchar * g_strdup_vprintf (constgchar *format, va_list args);
 gchar * g_strnfill (gsize length, gchar fill_char);
 ```

 * GLib implements many common data structures, like linked lists, sorted binary trees, N-ary trees, and hash tables.

 * GLib provides generic single and doubly linked lists, `GSList` and `GList`, respectively. 

 * Every GTK+ widget is a subclass of the GObject base class. So knowing the basic concepts of GObject is important for using a GTK+ widget or another GObject-based utility, but also for creating your own GObject classes.

 * What GObject adds is more features such as reference counting, inheri-tance, virtual functions, interfaces, signals and more.

 # PyGTK

 * `PyGObject` is a Python module that enables developers to access GObject-based libraries such as GTK+ within Python.

 * gobject-introspection (gi)