#!/usr/bin/env python
# -*- Mode: Python; py-indent-offset: 4 -*-

# This script creates the files "gtkextramodule_defs.h" and
# "gtkextramodule_impl.h".  Both files are required by the bindings
# for PyGTK 0.6.x.

import sys, os, string, re
sys.path.insert(0, os.path.join(os.pardir, 'codegen'))
import defsparser, generate

overrides = [
    "gtk_color_combo_new_with_values",
    "gtk_plot3d_new_with_size",
    "gtk_plot_csurface_new_function",
    "gtk_plot_data_new_function",
    "gtk_plot_new_with_size",
    "gtk_plot_polar_new_with_size",
    "gtk_plot_surface_new_function",
    "gtk_sheet_new_browser",
    "gtk_sheet_new_with_custom_entry",
    "gtk_plot_set_pc",
    "gtk_plot_canvas_set_pc",
    "gtk_plot_data_new_iterator",
    ]

types = {
    "GtkJustification": "int",
    "GtkOrientation": "int",
    "GtkPlotAxisPos": "int",
    "GtkPlotBorderStyle": "int",
    "GtkPlotCanvasArrow": "int",
    "GtkPlotCanvasSelection": "int",
    "GtkPlotCanvasSelectionMode": "int",
    "GtkPlotConnector": "int",
    "GtkPlotLineStyle": "int",
    "GtkPlotOrientation": "int",
    "GtkPlotPlane": "int",
    "GtkPlotScale": "int",
    "GtkPlotSide": "int",
    "GtkPlotSymbolStyle": "int",
    "GtkPlotSymbolType": "int",
    "GtkStateType": "int",
    "GtkType": "uint",
    "const-GdkColor*": "GdkColor",
    "const-gchar*": "string",
    "gboolean": "bool",
    "gchar*": "string",
    "gdouble": "double",
    "gfloat": "float",
    "gint": "int",
    "guint": "uint",
    "guint16": "uint",
    }

def maptype(type):
    if types.has_key(type):
        type = types[type]
    else:
        type = string.replace(type, "*", "")
    return type

def mapret(type):
    type = maptype(type)
    if type == "string":
        type = "static_string"
    return type
    
def write_defs(parser, overrides, fp=sys.stdout):
    fp.write("; -*- scheme -*-\n\n")
    for o in parser.objects:
        fp.write("(define-object Gtk" + o.name + " (" + o.parent + ")")
        if o.fields:
            fp.write("\n  (fields")
            for (type, name) in o.fields:
                fp.write("\n   (" + maptype(type) + " " + name + ")")
            fp.write(")")
        fp.write(")\n\n")
    for f in parser.functions:
        if f.c_name in overrides:
            fp.write(";(define-func " + f.c_name + ")\n\n")
        else:
            fp.write("(define-func " + f.c_name + "\n  " + mapret(f.ret)
                     + "\n  (")
            n = 0
            if isinstance(f, defsparser.MethodDef):
                fp.write("(" + f.of_object + " obj)")
                n = n + 1
            for (type, name, default, nullok) in f.params:
                if n:
                    fp.write("\n   ")
                fp.write("(" + maptype(type) + " " + name)
                if nullok:
                    fp.write(" (null-ok)")
                if default:
                    fp.write(" (= \"" + default + "\")")
                fp.write(")")
                n = n + 1
            fp.write ("))\n\n")

def read_overrides(filename):
    rexp = re.compile('_wrap_([a-zA-Z0-9_]*),')
    input = open(filename)
    while 1:
        line = input.readline()
        if not line:
            break
        match = rexp.search(line)
        if match:
            overrides.append(match.group(1))
    input.close()
    return overrides

if __name__ == '__main__':
    # Convert the new defs into old defs.
    overrides = read_overrides('gtkextramodule.c')
    parser = defsparser.DefsParser('gtkextra.defs')
    parser.startParsing()
    defsname = os.tmpnam()
    defs = open(defsname, "w")
    write_defs(parser, overrides, defs)
    defs.close()
    # Create gtkextramodule_defs.h and gtkextramodule_impl.h.
    p = generate.FilteringParser(input=defsname,
                                 prefix='gtkextramodule')
    generate.TypesParser.define_object(p, "GtkWidget")
    generate.TypesParser.define_object(p, "GtkAdjustment")
    p.startParsing()
    os.unlink(defsname)
