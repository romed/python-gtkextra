#!/usr/bin/env python

import string, commands, glob, os
from distutils.core import setup, Extension

def filteropt(s, opts):
    list = []
    args = string.split(s)
    for opt in opts:
        a = []
        i = 0
        while i < len(args):
            arg = args[i]
            n = len(arg)
            if n >= 2 and arg[0] == "-" and arg[1] == opt:
                del args[i]
                if n > 2:
                    a.append(arg[2:])
                elif args:
                    arg = args[i]
                    del args[i]
            else:
                i = i + 1
        list.append(a)
    list.append(args)
    return list

gtk_cflags = commands.getoutput("gtk-config --cflags")
gtk_libs = commands.getoutput("gtk-config --libs")

(include_dirs, extra_compile_args) = filteropt(gtk_cflags, "I")
(library_dirs, libraries, extra_link_args) = filteropt(gtk_libs, "Ll")

libraries.insert(0, "gtkextra")

sources = glob.glob(os.path.join("gtkextra", "*.c"))

setup (name = "python-gtkextra",
       version = "0.21",
       description = "Python bindings for the GtkExtra widget set",
       long_description = "This package contains modules that allow "\
                          "you to use the GtkExtra widget set in "\
                          "Python programs.  GtkExtra provides a "\
                          "spreadsheet-like matrix widget and widgets "\
                          "for 2-D and 3-D graphing.",
       licence = "LGPL",
       author = "Andreas Voegele",
       author_email = "voegelas@users.sourceforge.net",
       url = "http://python-gtkextra.sourceforge.net/",
       packages = ["gtkextra"],
       ext_modules = [Extension("gtkextra._gtkextramodule", sources,
                                include_dirs=include_dirs,
                                library_dirs=library_dirs,
                                libraries=libraries,
                                extra_compile_args=extra_compile_args,
                                extra_link_args=extra_link_args)])
