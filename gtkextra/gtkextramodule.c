/* -*- Mode: C; c-basic-offset: 4 -*- */
/*
 * Python bindings for the GtkExtra widget set
 *
 * Copyright (C) 2000-2002 Andreas Voegele
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Don't forget to add your wrapper functions to the array at the end
 * of this file!
 */
 
#include "pygtkextra-private.h"

/*
 * GtkSheet
 */

static PyObject *
_wrap_gtk_sheet_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    int rows, columns;
    char *title = NULL;
    PyObject *entry_type = Py_None;
    int editable = TRUE;

    if (!PyArg_ParseTuple(args, "ii|zOi:gtk_sheet_new", &rows, &columns,
			  &title, &entry_type, &editable))
        return NULL;
    if (editable) {
	if (entry_type == Py_None) {
	    widget = gtk_sheet_new(rows, columns, title);
	} else {
	    if (!PyInt_Check(entry_type)) {
		PyErr_SetString(PyExc_TypeError, "entry_type must be integer");
		return NULL;
	    }
	    widget =
		gtk_sheet_new_with_custom_entry(rows, columns, title, (GtkType)
						PyInt_AS_LONG(entry_type));
	}
    } else {
	widget = gtk_sheet_new_browser(rows, columns, title);
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkSheet object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_sheet_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_sheet_get_entry(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkWidget *entry_widget;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_entry", &PyGtk_Type, &obj))
        return NULL;
    entry_widget = gtk_sheet_get_entry(GTK_SHEET(PyGtk_Get(obj)));
    if (entry_widget)
	return PyGtk_New(GTK_OBJECT(entry_widget));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_entry_widget(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkWidget *entry_widget;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_entry_widget",
			  &PyGtk_Type, &obj))
        return NULL;
    entry_widget = gtk_sheet_get_entry_widget(GTK_SHEET(PyGtk_Get(obj)));
    if (entry_widget)
	return PyGtk_New(GTK_OBJECT(entry_widget));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_visible_range(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_visible_range",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_sheet_get_visible_range(GTK_SHEET(PyGtk_Get(obj)), &range);
    return pygtkextra_sheet_range_new(&range);
}

static PyObject *
_wrap_gtk_sheet_clip_range(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;

    if (!PyArg_ParseTuple(args, "O!(iiii):gtk_sheet_clip_range",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!O:gtk_sheet_clip_range",
			       &PyGtk_Type, &obj, &arg)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_clip_range(GTK_SHEET(PyGtk_Get(obj)), rangep);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_vadjustment(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkAdjustment *adjustment;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_vadjustment",
			  &PyGtk_Type, &obj))
        return NULL;
    adjustment = gtk_sheet_get_vadjustment(GTK_SHEET(PyGtk_Get(obj)));
    if (adjustment)
	return PyGtk_New(GTK_OBJECT(adjustment));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_hadjustment(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkAdjustment *adjustment;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_hadjustment",
			  &PyGtk_Type, &obj))
        return NULL;
    adjustment = gtk_sheet_get_hadjustment(GTK_SHEET(PyGtk_Get(obj)));
    if (adjustment)
	return PyGtk_New(GTK_OBJECT(adjustment));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_select_range(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;

    if (!PyArg_ParseTuple(args, "O!(iiii):gtk_sheet_select_range",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!O:gtk_sheet_select_range",
			       &PyGtk_Type, &obj, &arg)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_select_range(GTK_SHEET(PyGtk_Get(obj)), rangep);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_active_cell(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gint row, column;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_active_cell",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_sheet_get_active_cell(GTK_SHEET(PyGtk_Get(obj)), &row, &column);
    if (row < 0 || column < 0) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    return Py_BuildValue("(ii)", (int) row, (int) column);
}

static PyObject *
_wrap_gtk_sheet_cell_get_text(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    char *string;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_cell_get_text",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    string = gtk_sheet_cell_get_text(GTK_SHEET(PyGtk_Get(obj)), row, column);
    return PyString_FromString((string) ? string : "");
}

static PyObject *
_wrap_gtk_sheet_range_clear(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;

    if (!PyArg_ParseTuple(args, "O!(iiii):gtk_sheet_range_clear",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!O:gtk_sheet_range_clear",
			       &PyGtk_Type, &obj, &arg)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_clear(GTK_SHEET(PyGtk_Get(obj)), rangep);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_delete(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;

    if (!PyArg_ParseTuple(args, "O!(iiii):gtk_sheet_range_delete",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!O:gtk_sheet_range_delete",
			       &PyGtk_Type, &obj, &arg)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    /* If a range is deleted the reference count of all objects linked
       to cells in the given range must be decremented. */
    pygtkextra_sheet_unref_links(GTK_SHEET(PyGtk_Get(obj)), rangep);
    gtk_sheet_range_delete(GTK_SHEET(PyGtk_Get(obj)), rangep);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_link_cell(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    PyObject *object;
    gpointer link;

    if (!PyArg_ParseTuple(args, "O!iiO:gtk_sheet_link_cell",
			  &PyGtk_Type, &obj, &row, &column, &object))
        return NULL;
    if (object == Py_None)
	link = NULL;
    else {
	Py_INCREF(object);
	link = (gpointer) object;
    }
    /* If a new object is linked to the cell the reference count of the old
       object must be decremented. */
    object = (PyObject *) gtk_sheet_get_link(GTK_SHEET(PyGtk_Get(obj)),
					     row, column);
    Py_XDECREF(object);
    gtk_sheet_link_cell(GTK_SHEET(PyGtk_Get(obj)), row, column, link);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    PyObject *object;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_get_link",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    object = (PyObject *) gtk_sheet_get_link(GTK_SHEET(PyGtk_Get(obj)),
					     row, column);
    if (!object)
	object = Py_None;
    Py_INCREF(object);
    return object;
}

static PyObject *
_wrap_gtk_sheet_remove_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    PyObject *object;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_remove_link",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    /* The reference count of the removed object must be decremented. */
    object = (PyObject *) gtk_sheet_get_link(GTK_SHEET(PyGtk_Get(obj)),
					     row, column);
    Py_XDECREF(object);
    gtk_sheet_remove_link(GTK_SHEET(PyGtk_Get(obj)), row, column);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_pixel_info(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int x, y;
    gint row, column;
    
    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_get_pixel_info",
			  &PyGtk_Type, &obj, &x, &y))
        return NULL;
    if (!gtk_sheet_get_pixel_info(GTK_SHEET(PyGtk_Get(obj)), x, y,
				  &row, &column)) {
	/* Like gtk_clist_get_selection_info() this function returns
	   None if you click outside of the cells. */
	Py_INCREF(Py_None);
	return Py_None;
    }
    return Py_BuildValue("(ii)", (int) row, (int) column);
}

static PyObject *
_wrap_gtk_sheet_get_cell_area(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    GdkRectangle area;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_get_cell_area",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    if (!gtk_sheet_get_cell_area(GTK_SHEET(PyGtk_Get(obj)), row, column,
				 &area)) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    return Py_BuildValue("(iiii)", (int) area.x, (int) area.y,
			 (int) area.width, (int) area.height);
}

static PyObject *
_wrap_gtk_sheet_range_set_background(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    PyObject *py_color;
    GdkColor *color;

    if (!PyArg_ParseTuple(args, "O!(iiii)O:gtk_sheet_range_set_background",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &py_color)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!OO:gtk_sheet_range_set_background",
			       &PyGtk_Type, &obj, &arg, &py_color)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    if (PyGdkColor_Check(py_color))
        color = PyGdkColor_Get(py_color);
    else if (py_color == Py_None)
	color = NULL;
    else {
        PyErr_SetString(PyExc_TypeError,
			"color argument must be a GdkColor or None");
	return NULL;
    }
    gtk_sheet_range_set_background(GTK_SHEET(PyGtk_Get(obj)), rangep, color);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_foreground(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    PyObject *py_color;
    GdkColor *color;

    if (!PyArg_ParseTuple(args, "O!(iiii)O:gtk_sheet_range_set_foreground",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &py_color)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!OO:gtk_sheet_range_set_foreground",
			       &PyGtk_Type, &obj, &arg, &py_color)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    if (PyGdkColor_Check(py_color))
        color = PyGdkColor_Get(py_color);
    else if (py_color == Py_None)
	color = NULL;
    else {
        PyErr_SetString(PyExc_TypeError,
			"color argument must be a GdkColor or None");
	return NULL;
    }
    gtk_sheet_range_set_foreground(GTK_SHEET(PyGtk_Get(obj)), rangep, color);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_justification(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    int justification;

    if (!PyArg_ParseTuple(args, "O!(iiii)i:gtk_sheet_range_set_justification",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &justification)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!Oi:gtk_sheet_range_set_justification",
			       &PyGtk_Type, &obj, &arg, &justification)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_set_justification(GTK_SHEET(PyGtk_Get(obj)), rangep,
				      justification);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_editable(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    int editable;

    if (!PyArg_ParseTuple(args, "O!(iiii)i:gtk_sheet_range_set_editable",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &editable)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!Oi:gtk_sheet_range_set_editable",
			       &PyGtk_Type, &obj, &arg, &editable)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_set_editable(GTK_SHEET(PyGtk_Get(obj)), rangep, editable);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_visible(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    int visible;

    if (!PyArg_ParseTuple(args, "O!(iiii)i:gtk_sheet_range_set_visible",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &visible)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!Oi:gtk_sheet_range_set_visible",
			       &PyGtk_Type, &obj, &arg, &visible)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_set_visible(GTK_SHEET(PyGtk_Get(obj)), rangep, visible);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_border(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    int mask, width, line_style = GDK_LINE_SOLID;

    if (!PyArg_ParseTuple(args, "O!(iiii)ii|i:gtk_sheet_range_set_border",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &mask, &width,
			  &line_style)) {
	PyObject *arg;
	
	line_style = GDK_LINE_SOLID;
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!Oii|i:gtk_sheet_range_set_border",
			       &PyGtk_Type, &obj, &arg, &mask, &width,
			       &line_style)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_set_border(GTK_SHEET(PyGtk_Get(obj)), rangep, mask,
			       width, line_style);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_border_color(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    PyObject *py_color;

    if (!PyArg_ParseTuple(args, "O!(iiii)O!:gtk_sheet_range_set_border_color",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &PyGdkColor_Type,
			  &py_color)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!OO!:gtk_sheet_range_set_border_color",
			       &PyGtk_Type, &obj, &arg,
			       &PyGdkColor_Type, &py_color)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    gtk_sheet_range_set_border_color(GTK_SHEET(PyGtk_Get(obj)), rangep,
				     PyGdkColor_Get(py_color));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_range_set_font(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkSheetRange range, *rangep = &range;
    PyObject *py_font;

    if (!PyArg_ParseTuple(args, "O!(iiii)O!:gtk_sheet_range_set_font",
			  &PyGtk_Type, &obj, &range.row0, &range.col0,
			  &range.rowi, &range.coli, &PyGdkFont_Type,
			  &py_font)) {
	PyObject *arg;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!OO!:gtk_sheet_range_set_font",
			       &PyGtk_Type, &obj, &arg, &PyGdkFont_Type,
			       &py_font)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "range argument must be 4-sequence or None");
	    return NULL;
	}
	
	rangep = NULL;
    }
    /* The Python program will crash if it doesn't keep a reference to the
       GdkFont object. */
    gtk_sheet_range_set_font(GTK_SHEET(PyGtk_Get(obj)), rangep,
			     PyGdkFont_Get(py_font));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    gboolean is_allocated;
    GtkSheetCellAttr attributes;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_get_attributes",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    if (row < 0 || column < 0) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    is_allocated = gtk_sheet_get_attributes(GTK_SHEET(PyGtk_Get(obj)),
					    row, column, &attributes);
    /* In Python the GtkSheetCellAttr type has an additional attribute
       that is called "is_allocated". */
    return pygtkextra_sheet_cell_attr_new(&attributes, is_allocated);
}

static PyObject *
_wrap_gtk_sheet_put(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *widget;
    int x, y;
    GtkSheetChild *child;

    if (!PyArg_ParseTuple(args, "O!O!ii:gtk_sheet_put", &PyGtk_Type, &obj,
			  &PyGtk_Type, &widget, &x, &y))
        return NULL;
    child = gtk_sheet_put(GTK_SHEET(PyGtk_Get(obj)),
			  GTK_WIDGET(PyGtk_Get(widget)), x, y);
    if (!child) {
	PyErr_SetString(PyExc_RuntimeError, "cannot put child into sheet");
	return NULL;
    }
    return pygtkextra_sheet_child_new(child);
}

static PyObject *
_wrap_gtk_sheet_get_child_at(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row, column;
    GtkSheetChild *child;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_sheet_get_child_at",
			  &PyGtk_Type, &obj, &row, &column))
        return NULL;
    child = gtk_sheet_get_child_at(GTK_SHEET(PyGtk_Get(obj)), row, column);
    return pygtkextra_sheet_child_new(child);
}

static PyObject *
_wrap_gtk_sheet_get_column_title(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int column;
    char *title;

    if (!PyArg_ParseTuple(args, "O!i:gtk_sheet_get_column_title",
			  &PyGtk_Type, &obj, &column))
        return NULL;
    if (column < 0
	|| column >= gtk_sheet_get_columns_count(GTK_SHEET(PyGtk_Get(obj)))) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    title = GTK_SHEET(PyGtk_Get(obj))->column[column].name;
    if (title)
	return PyString_FromString(title);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_row_title(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row;
    char *title;

    if (!PyArg_ParseTuple(args, "O!i:gtk_sheet_get_row_title",
			  &PyGtk_Type, &obj, &row))
        return NULL;
    if (row < 0
	|| row >= gtk_sheet_get_rows_count(GTK_SHEET(PyGtk_Get(obj)))) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    title = GTK_SHEET(PyGtk_Get(obj))->row[row].name;
    if (title)
	return PyString_FromString(title);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_sheet_get_column_width(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int column;

    if (!PyArg_ParseTuple(args, "O!i:gtk_sheet_get_column_width",
			  &PyGtk_Type, &obj, &column))
        return NULL;
    if (column < 0
	|| column >= gtk_sheet_get_columns_count(GTK_SHEET(PyGtk_Get(obj)))) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    return PyInt_FromLong(GTK_SHEET(PyGtk_Get(obj))->column[column].width);
}

static PyObject *
_wrap_gtk_sheet_get_row_height(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int row;

    if (!PyArg_ParseTuple(args, "O!i:gtk_sheet_get_row_height",
			  &PyGtk_Type, &obj, &row))
        return NULL;
    if (row < 0
	|| row >= gtk_sheet_get_rows_count(GTK_SHEET(PyGtk_Get(obj)))) {
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    return PyInt_FromLong(GTK_SHEET(PyGtk_Get(obj))->row[row].height);
}

static PyObject *
_wrap_gtk_sheet_get_range(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_sheet_get_range", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_sheet_range_new(&(GTK_SHEET(PyGtk_Get(obj))->range));
}

/* wrapper for the signal "traverse" */
static PyObject *
_gtk_sheet_callback_wrapper(PyObject *self, PyObject *args)
{
    int len;
    PyObject *tuple, *ret;
    int *rowp = NULL, *columnp = NULL;
    PyObject *row, *column;

    len = PyTuple_Size(args) - 1;
    tuple = PyTuple_GetSlice(args, 0, len);
    if (!tuple)
	return NULL;
    row = PyTuple_GetItem(tuple, 3);
    column = PyTuple_GetItem(tuple, 4);
    if (PyCObject_Check(row) && PyCObject_Check(column)) {
	rowp = (int *) PyCObject_AsVoidPtr(row);
	columnp = (int *) PyCObject_AsVoidPtr(column);
	if (rowp && columnp) {
	    row = PyInt_FromLong(*rowp);
	    if (row)
		PyTuple_SetItem(tuple, 3, row);
	    column = PyInt_FromLong(*columnp);
	    if (column)
		PyTuple_SetItem(tuple, 4, column);
	}
    }
    ret = PyEval_CallObject(PyTuple_GetItem(args, len), tuple);
    Py_DECREF(tuple);
    if (PySequence_Check(ret)) {
	if (PySequence_Length(ret) == 2) {
	    row = PySequence_GetItem(ret, 0);
	    column = PySequence_GetItem(ret, 1);
	    if (row && PyInt_Check(row) && column && PyInt_Check(column)) {
		if (rowp && columnp) {
		    *rowp = (int) PyInt_AS_LONG(row);
		    *columnp = (int) PyInt_AS_LONG(column);
		    Py_DECREF(ret);
		    ret = PyInt_FromLong(1);
		} else {
		    PyErr_SetString(PyExc_RuntimeError,
				    "cannot set row and column");
		    Py_DECREF(ret);
		    ret = NULL;
		}
	    }
	    Py_XDECREF(row);
	    Py_XDECREF(column);
	}
    }
    return ret;
}


/*
 * GtkPlotData
 */

static PyObject *
_wrap_gtk_plot_data_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *function = Py_None, *extra = NULL;

    if (!PyArg_ParseTuple(args, "|OO!:gtk_plot_data_new", &function,
			  &PyTuple_Type, &extra))
        return NULL;
    if (function == Py_None) {
	widget = gtk_plot_data_new();
    } else if (PyCallable_Check(function)) {
	widget =
	    gtk_plot_data_new_function(pygtkextra_plot_data_call_plot_function);
	if (widget)
	    pygtkextra_plot_data_register_plot_function(GTK_PLOT_DATA(widget),
							function, extra);
    } else if (PyTuple_Check(function)) {
	PyObject *iterator;
	int n, mask;
	
	if (!PyArg_ParseTuple(function, "Oii:gtk_plot_data_new", &iterator,
			      &n, &mask))
	    return NULL;
	if (!PyCallable_Check(iterator)) {
	    PyErr_SetString(PyExc_TypeError, "iterator must be callable");
	    return NULL;
	}
	widget =
	    gtk_plot_data_new_iterator((GtkPlotIterator)
				       pygtkextra_plot_data_call_plot_iterator,
				       n, mask);
	if (widget)
	    pygtkextra_plot_data_register_plot_iterator(GTK_PLOT_DATA(widget),
							iterator, extra);
    } else if (PyCObject_Check(function)) {
	if (extra && PyTuple_Size(extra) > 0) {
	    PyErr_SetString(PyExc_TypeError,
			    "cannot pass extra arguments to C function");
	    return NULL;
	}
	widget =
	    gtk_plot_data_new_function((GtkPlotFunc)
				       PyCObject_AsVoidPtr(function));
    } else {
        PyErr_SetString(PyExc_TypeError,
			"function argument must be callable or None");
	return NULL;
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotData object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_plot_data_set_points(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *x, *y, *dx = Py_None, *dy = Py_None;
    int n = -1;

    if (!PyArg_ParseTuple(args, "O!(OOOOi):gtk_plot_data_set_points",
			  &PyGtk_Type, &obj, &x, &y, &dx, &dy, &n)) {
	PyErr_Clear();
	if (!PyArg_ParseTuple(args, "O!OO|OOi:gtk_plot_data_set_points",
			      &PyGtk_Type, &obj, &x, &y, &dx, &dy, &n))
	    return NULL;
    }
    return pygtkextra_plot_data_set_points(GTK_PLOT_DATA(PyGtk_Get(obj)),
					   x, y, dx, dy, n);
}

static PyObject *
_wrap_gtk_plot_data_get_points(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_points",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_points(GTK_PLOT_DATA(PyGtk_Get(obj)));
}

static PyObject *
_wrap_gtk_plot_data_get_point(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int i;
    gdouble x = 0.0, y = 0.0, z = 0.0, a = 0.0, dx = 0.0, dy = 0.0,
	dz = 0.0, da = 0.0;
    gchar *label = NULL;
    gboolean error;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_data_get_point",
			  &PyGtk_Type, &obj, &i))
        return NULL;
    gtk_plot_data_get_point(GTK_PLOT_DATA(PyGtk_Get(obj)), i, &x, &y, &z, &a,
			    &dx, &dy, &dz, &da, &label, &error);
    if (error) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    return Py_BuildValue("(dddddddds)", (double) x, (double) y, (double) z,
			 (double) a, (double) dx, (double) dy, (double) dz,
			 (double) da, label);
}

static PyObject *
_wrap_gtk_plot_data_set_numpoints(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int n;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_data_set_numpoints",
			  &PyGtk_Type, &obj, &n))
        return NULL;
    return pygtkextra_plot_data_set_numpoints(GTK_PLOT_DATA(PyGtk_Get(obj)),
					      n);
}

static PyObject *
_wrap_gtk_plot_data_set_x(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_x", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  0, array);
}

static PyObject *
_wrap_gtk_plot_data_set_y(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_y", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  1, array);
}

static PyObject *
_wrap_gtk_plot_data_set_z(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_z", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  2, array);
}

static PyObject *
_wrap_gtk_plot_data_set_a(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_a", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  3, array);
}

static PyObject *
_wrap_gtk_plot_data_set_dx(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_dx", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  4, array);
}

static PyObject *
_wrap_gtk_plot_data_set_dy(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_dy", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  5, array);
}

static PyObject *
_wrap_gtk_plot_data_set_dz(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_dz", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  6, array);
}

static PyObject *
_wrap_gtk_plot_data_set_da(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_da", &PyGtk_Type, &obj,
			  &array))
        return NULL;
    return pygtkextra_plot_data_set_array(GTK_PLOT_DATA(PyGtk_Get(obj)),
					  7, array);
}

static PyObject *
_wrap_gtk_plot_data_get_x(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_x", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 0);
}

static PyObject *
_wrap_gtk_plot_data_get_y(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_y", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 1);
}

static PyObject *
_wrap_gtk_plot_data_get_z(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_z", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 2);
}

static PyObject *
_wrap_gtk_plot_data_get_a(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_a", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 3);
}

static PyObject *
_wrap_gtk_plot_data_get_dx(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_dx", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 4);
}

static PyObject *
_wrap_gtk_plot_data_get_dy(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_dy", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 5);
}

static PyObject *
_wrap_gtk_plot_data_get_dz(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_dz", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 6);
}

static PyObject *
_wrap_gtk_plot_data_get_da(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_da", &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_array(GTK_PLOT_DATA(PyGtk_Get(obj)), 7);
}

static PyObject *
_wrap_gtk_plot_data_set_labels(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *labels;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_labels",
			  &PyGtk_Type, &obj, &labels))
        return NULL;
    return pygtkextra_plot_data_set_labels(GTK_PLOT_DATA(PyGtk_Get(obj)),
					   labels);
}

static PyObject *
_wrap_gtk_plot_data_get_labels(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_labels",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_data_get_labels(GTK_PLOT_DATA(PyGtk_Get(obj)));
}

static PyObject *
_wrap_gtk_plot_data_set_symbol(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int symbol_type, symbol_style, size, line_width;
    PyObject *color, *border_color = Py_None;

    if (!PyArg_ParseTuple(args, "O!iiiiO!|O:gtk_plot_data_set_symbol",
			  &PyGtk_Type, &obj, &symbol_type, &symbol_style,
			  &size, &line_width, &PyGdkColor_Type, &color,
			  &border_color))
        return NULL;
    if (border_color == Py_None) {
	border_color = color;
    } else if (!PyGdkColor_Check(border_color)) {
	PyErr_SetString(PyExc_TypeError,
			"border_color argument must be a GdkColor or None");
    }
    gtk_plot_data_set_symbol(GTK_PLOT_DATA(PyGtk_Get(obj)), symbol_type,
			     symbol_style, size, line_width,
			     PyGdkColor_Get(color),
			     PyGdkColor_Get(border_color));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_data_get_symbol(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gint size;
    gfloat line_width;
    GtkPlotSymbolType symbol_type;
    GtkPlotSymbolStyle symbol_style;
    GdkColor color, border_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_symbol",
			  &PyGtk_Type, &obj))
	return NULL;
    gtk_plot_data_get_symbol(GTK_PLOT_DATA(PyGtk_Get(obj)), &symbol_type,
			     &symbol_style, &size, &line_width, &color,
			     &border_color);
    return Py_BuildValue("(iiidNN)", (int) symbol_type, (int) symbol_style,
			 (int) size, (double) line_width,
			 PyGdkColor_New(&color),
			 PyGdkColor_New(&border_color));
}

static PyObject *
_wrap_gtk_plot_data_get_line_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotLineStyle line_style;
    gfloat line_width;
    GdkColor line_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_line_attributes",
			  &PyGtk_Type, &obj))
	return NULL;
    gtk_plot_data_get_line_attributes(GTK_PLOT_DATA(PyGtk_Get(obj)),
				      &line_style, &line_width, &line_color);
    return pygtkextra_plot_line_new(line_style, line_width, &line_color);
}

static PyObject *
_wrap_gtk_plot_data_get_gradient_colors(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GdkColor min_color, max_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_gradient_colors",
			  &PyGtk_Type, &obj))
	return NULL;
    gtk_plot_data_get_gradient_colors(GTK_PLOT_DATA(PyGtk_Get(obj)),
				      &min_color, &max_color);
    return Py_BuildValue("(NN)", PyGdkColor_New(&min_color),
			 PyGdkColor_New(&max_color));
}

static PyObject *
_wrap_gtk_plot_data_get_gradient(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble min, max;
    gint levels, sublevels;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_gradient",
			  &PyGtk_Type, &obj))
	return NULL;
    gtk_plot_data_get_gradient(GTK_PLOT_DATA(PyGtk_Get(obj)), &min, &max,
			       &levels, &sublevels);
    return Py_BuildValue("(ddii)", (double) min, (double) max,
			 (int) levels, (int) sublevels);
}

static PyObject *
_wrap_gtk_plot_data_get_gradient_level(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int level;
    GdkColor color;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_data_get_gradient",
			  &PyGtk_Type, &obj, &level))
	return NULL;
    gtk_plot_data_get_gradient_level(GTK_PLOT_DATA(PyGtk_Get(obj)), level,
				     &color);
    return PyGdkColor_New(&color);
}

static PyObject *
_wrap_gtk_plot_data_set_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *object;
    gpointer link;
    
    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_data_set_link",
			  &PyGtk_Type, &obj, &object))
	return NULL;
    Py_INCREF(object);
    if (object == Py_None)
	link = NULL;
    else {
	Py_INCREF(object);
	link = (gpointer) object;
    }
     /* If a new object is linked to the cell the reference count of the old
       object must be decremented. */
    object = (PyObject *)
	gtk_plot_data_get_link(GTK_PLOT_DATA(PyGtk_Get(obj)));
    Py_XDECREF(object);
    gtk_plot_data_set_link(GTK_PLOT_DATA(PyGtk_Get(obj)), link);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_data_get_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *object;
    
    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_get_link",
			  &PyGtk_Type, &obj))
	return NULL;
    object = (PyObject *)
	gtk_plot_data_get_link(GTK_PLOT_DATA(PyGtk_Get(obj)));
    if (!object)
	object = Py_None;
    Py_INCREF(object);
    return object;
}

static PyObject *
_wrap_gtk_plot_data_remove_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *object;
    
    if (!PyArg_ParseTuple(args, "O!:gtk_plot_data_remove_link",
			  &PyGtk_Type, &obj))
	return NULL;
    /* The reference count of the removed object must be decremented. */
    object = (PyObject *)
	gtk_plot_data_get_link(GTK_PLOT_DATA(PyGtk_Get(obj)));
    Py_XDECREF(object);
    gtk_plot_data_remove_link(GTK_PLOT_DATA(PyGtk_Get(obj)));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_data_add_marker(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int i;
    GtkPlotMarker *marker;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_data_add_marker",
			  &PyGtk_Type, &obj, &i))
	return NULL;
    marker = gtk_plot_data_add_marker(GTK_PLOT_DATA(PyGtk_Get(obj)), i);
    if (marker)
	return PyCObject_FromVoidPtr(marker, NULL);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_data_remove_marker(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_marker;
    GtkPlotMarker *marker;
    gboolean ok;

    if (!PyArg_ParseTuple(args, "O!O!:gtk_plot_data_remove_marker",
			  &PyGtk_Type, &obj, &PyCObject_Type, &py_marker))
	return NULL;
    marker = PyCObject_AsVoidPtr(py_marker);
    ok = gtk_plot_data_remove_marker(GTK_PLOT_DATA(PyGtk_Get(obj)), marker);
    return PyInt_FromLong(ok);
}


/*
 * GtkPlotBar
 */

static PyObject *
_wrap_gtk_plot_bar_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    int orientation = GTK_ORIENTATION_VERTICAL;

    if (!PyArg_ParseTuple(args, "|i:gtk_plot_bar_new", &orientation))
        return NULL;
    widget = gtk_plot_bar_new(orientation);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError, "cannot create GtkPlotBar object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkPlotBox
 */

static PyObject *
_wrap_gtk_plot_box_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    int orientation = GTK_ORIENTATION_VERTICAL;

    if (!PyArg_ParseTuple(args, "|i:gtk_plot_box_new", &orientation))
        return NULL;
    widget = gtk_plot_box_new(orientation);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError, "cannot create GtkPlotBox object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkPlotFlux
 */

static PyObject *
_wrap_gtk_plot_flux_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;

    if (!PyArg_ParseTuple(args, ":gtk_plot_flux_new"))
        return NULL;
    widget = gtk_plot_flux_new();
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotFlux object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_plot_flux_get_arrow(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gint arrow_length, arrow_width;
    GtkPlotSymbolStyle symbol_style;
    
    if (!PyArg_ParseTuple(args, "O!:gtk_plot_flux_get_arrow",
			  &PyGtk_Type, &obj))
	return NULL;
    gtk_plot_flux_get_arrow(GTK_PLOT_FLUX(PyGtk_Get(obj)), &arrow_length,
			    &arrow_width, &symbol_style);
    return Py_BuildValue("(iii)", (int) arrow_length, (int) arrow_width,
			 (int) symbol_style);
}


/*
 * GtkPlotSurface
 */

static PyObject *
_wrap_gtk_plot_surface_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *function = Py_None, *extra = NULL;

    if (!PyArg_ParseTuple(args, "|OO!:gtk_plot_surface_new", &function,
			  &PyTuple_Type, &extra))
        return NULL;
    if (function == Py_None) {
	widget = gtk_plot_surface_new();
    } else if (PyCallable_Check(function)) {
	widget =
	    gtk_plot_surface_new_function(pygtkextra_plot_data_call_plot3d_function);
	if (widget)
	    pygtkextra_plot_data_register_plot3d_function(GTK_PLOT_DATA(widget),
							  function, extra);
    } else if (PyCObject_Check(function)) {
	if (extra && PyTuple_Size(extra) > 0) {
	    PyErr_SetString(PyExc_TypeError,
			    "cannot pass extra arguments to C function");
	    return NULL;
	}
	widget =
	    gtk_plot_surface_new_function((GtkPlotFunc3D)
					  PyCObject_AsVoidPtr(function));
    } else {
        PyErr_SetString(PyExc_TypeError,
			"function argument must be callable or None");
	return NULL;
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotSurface object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_plot_surface_set_points(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *x, *y, *z, *dx, *dy, *dz;
    int nx, ny;

    if (!PyArg_ParseTuple(args, "O!(OOOOOOii):gtk_plot_surface_set_points",
			  &PyGtk_Type, &obj, &x, &y, &z, &dx, &dy, &dz,
			  &nx, &ny)) {
	PyErr_Clear();
	if (!PyArg_ParseTuple(args, "O!OOOOOOii:gtk_plot_surface_set_points",
			      &PyGtk_Type, &obj, &x, &y, &z, &dx, &dy, &dz,
			      &nx, &ny))
	    return NULL;
    }
    return pygtkextra_plot_surface_set_points(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					      x, y, z, dx, dy, dz, nx, ny);
}

static PyObject *
_wrap_gtk_plot_surface_get_points(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_points",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_points(GTK_PLOT_SURFACE(PyGtk_Get(obj)));
}

static PyObject *
_wrap_gtk_plot_surface_set_nx(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int nx;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_surface_set_nx",
			  &PyGtk_Type, &obj, &nx))
        return NULL;
    return pygtkextra_plot_surface_set_nx(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					  nx);
}

static PyObject *
_wrap_gtk_plot_surface_set_ny(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int ny;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_surface_set_ny",
			  &PyGtk_Type, &obj, &ny))
        return NULL;
    return pygtkextra_plot_surface_set_ny(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					  ny);
}

static PyObject *
_wrap_gtk_plot_surface_set_x(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_x",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     0, array);
}

static PyObject *
_wrap_gtk_plot_surface_set_y(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_y",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     1, array);
}

static PyObject *
_wrap_gtk_plot_surface_set_z(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_z",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     2, array);
}

static PyObject *
_wrap_gtk_plot_surface_set_dx(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_dx",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     4, array);
}

static PyObject *
_wrap_gtk_plot_surface_set_dy(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_dy",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     5, array);
}

static PyObject *
_wrap_gtk_plot_surface_set_dz(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *array;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_surface_set_dz",
			  &PyGtk_Type, &obj, &array))
        return NULL;
    return pygtkextra_plot_surface_set_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     6, array);
}

static PyObject *
_wrap_gtk_plot_surface_get_x(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_x",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     0);
}

static PyObject *
_wrap_gtk_plot_surface_get_y(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_y",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     1);
}

static PyObject *
_wrap_gtk_plot_surface_get_z(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_z",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     2);
}

static PyObject *
_wrap_gtk_plot_surface_get_dx(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_dx",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     4);
}

static PyObject *
_wrap_gtk_plot_surface_get_dy(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_dy",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     5);
}

static PyObject *
_wrap_gtk_plot_surface_get_dz(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_surface_get_dz",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_plot_surface_get_array(GTK_PLOT_SURFACE(PyGtk_Get(obj)),
					     6);
}


/*
 * GtkPlotCSurface
 */

static PyObject *
_wrap_gtk_plot_csurface_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *function = Py_None, *extra = NULL;

    if (!PyArg_ParseTuple(args, "|OO!:gtk_plot_csurface_new", &function,
			  &PyTuple_Type, &extra))
        return NULL;
    if (function == Py_None) {
	widget = gtk_plot_csurface_new();
    } else if (PyCallable_Check(function)) {
	widget =
	    gtk_plot_csurface_new_function(pygtkextra_plot_data_call_plot3d_function);
	if (widget)
	    pygtkextra_plot_data_register_plot3d_function(GTK_PLOT_DATA(widget),
							  function, extra);
    } else if (PyCObject_Check(function)) {
	if (extra && PyTuple_Size(extra) > 0) {
	    PyErr_SetString(PyExc_TypeError,
			    "cannot pass extra arguments to C function");
	    return NULL;
	}
	widget =
	    gtk_plot_csurface_new_function((GtkPlotFunc3D)
					   PyCObject_AsVoidPtr(function));
    } else {
        PyErr_SetString(PyExc_TypeError,
			"function argument must be callable or None");
	return NULL;
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotCSurface object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkPlotPixmap
 */

static PyObject *
_wrap_gtk_plot_pixmap_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *py_pixmap, *py_mask = Py_None;
    GdkBitmap *mask = NULL;

    if (!PyArg_ParseTuple(args, "O|O:gtk_plot_pixmap_new", &py_pixmap,
			  &py_mask))
        return NULL;
    if (!PyGdkWindow_Check(py_pixmap)) {
        PyErr_SetString(PyExc_TypeError,
			"pixmap argument must be a GdkPixmap");
	return NULL;
    }
    if (PyGdkWindow_Check(py_mask))
	mask = PyGdkWindow_Get(py_mask);
    else if (py_mask != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"mask argument must be a GdkBitmap or None");
	return NULL;
    }
    widget = gtk_plot_pixmap_new(PyGdkWindow_Get(py_pixmap), mask);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotPixmap object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkPlot
 */

static PyObject *
_wrap_gtk_plot_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *py_drawable = Py_None;
    PyObject *py_width = Py_None, *py_height = Py_None;
    GdkDrawable *drawable = NULL;

    if (!PyArg_ParseTuple(args, "|OOO:gtk_plot_new", &py_drawable,
			  &py_width, &py_height))
        return NULL;
    if (PyGdkWindow_Check(py_drawable))
        drawable = PyGdkWindow_Get(py_drawable);
    else if (py_drawable != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"drawable argument must be a GdkDrawable or None");
	return NULL;
    }
    if (py_width == Py_None && py_height == Py_None) {
	widget = gtk_plot_new(drawable);
    } else {
	PyObject *value;
	double width, height;

	if (PyNumber_Check(py_width)
	    && (value = PyNumber_Float(py_width))) {
	    width = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "width argument must be a number");
	    return NULL;
	}
	
	if (PyNumber_Check(py_height)
	    && (value = PyNumber_Float(py_height))) {
	    height = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "height argument must be a number");
	    return NULL;
	}
	
	widget = gtk_plot_new_with_size(drawable, width, height);
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlot object");
	return NULL;
    }
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_plot_get_position(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble x, y;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_get_position", &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_get_position(GTK_PLOT(PyGtk_Get(obj)), &x, &y);
    return Py_BuildValue("(dd)", (double) x, (double) y);
}

static PyObject *
_wrap_gtk_plot_get_size(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble width, height;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_get_size", &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_get_size(GTK_PLOT(PyGtk_Get(obj)), &width, &height);
    return Py_BuildValue("(dd)", (double) width, (double) height);
}

static PyObject *
_wrap_gtk_plot_get_internal_allocation(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkAllocation allocation;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_get_internal_allocation",
			  &PyGtk_Type, &obj))
        return NULL;
    allocation = gtk_plot_get_internal_allocation(GTK_PLOT(PyGtk_Get(obj)));
    return Py_BuildValue("(iiii)", (int) allocation.x, (int) allocation.y,
			 (int) allocation.width, (int) allocation.height);
}

static PyObject *
_wrap_gtk_plot_refresh(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int x, y, width, height;
    GdkRectangle area, *areap = &area;

    if (PyArg_ParseTuple(args, "O!(iiii):gtk_plot_refresh",
			 &PyGtk_Type, &obj, &x, &y, &width, &height)) {
	area.x = x;
	area.y = y;
	area.width = width;
	area.height = height;
    } else {
	PyObject *arg = Py_None;
	
	PyErr_Clear();
	if (!(PyArg_ParseTuple(args, "O!|O:gtk_plot_refresh",
			       &PyGtk_Type, &obj, &arg)
	      && arg == Py_None)) {
	    PyErr_SetString(PyExc_TypeError,
			    "area argument must be 4-sequence or None");
	    return NULL;
	}

	areap = NULL;
    }
    gtk_plot_refresh(GTK_PLOT(PyGtk_Get(obj)), areap);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_get_pixel(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x, y;
    gdouble out_x, out_y;

    if (!PyArg_ParseTuple(args, "O!dd:gtk_plot_get_pixel", &PyGtk_Type, &obj,
			  &x, &y))
        return NULL;
    gtk_plot_get_pixel(GTK_PLOT(PyGtk_Get(obj)), x, y, &out_x, &out_y);
    return Py_BuildValue("(dd)", (double) out_x, (double) out_y);
}

static PyObject *
_wrap_gtk_plot_get_point(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int x, y;
    gdouble out_x, out_y;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_plot_get_point", &PyGtk_Type, &obj,
			  &x, &y))
        return NULL;
    gtk_plot_get_point(GTK_PLOT(PyGtk_Get(obj)), x, y, &out_x, &out_y);
    return Py_BuildValue("(dd)", (double) out_x, (double) out_y);
}

static PyObject *
_wrap_gtk_plot_get_xrange(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble xmin, xmax;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_get_xrange", &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_get_xrange(GTK_PLOT(PyGtk_Get(obj)), &xmin, &xmax);
    return Py_BuildValue("(dd)", (double) xmin, (double) xmax);
}

static PyObject *
_wrap_gtk_plot_get_yrange(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble ymin, ymax;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_get_yrange", &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_get_yrange(GTK_PLOT(PyGtk_Get(obj)), &ymin, &ymax);
    return Py_BuildValue("(dd)", (double) ymin, (double) ymax);
}

static PyObject *
_wrap_gtk_plot_put_text(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *fontname, *string;
    PyObject *py_foreground = Py_None, *py_background = Py_None;
    GdkColor *foreground = NULL, *background = NULL;
    double x, y;
    int angle, height, transparent, justification;
    GtkPlotText *text;

    if (!PyArg_ParseTuple(args, "O!ddziiOOiiz:gtk_plot_put_text",
			  &PyGtk_Type, &obj, &x, &y, &fontname, &height,
			  &angle, &py_foreground, &py_background,
			  &transparent, &justification, &string))
        return NULL;
    if (PyGdkColor_Check(py_foreground))
        foreground = PyGdkColor_Get(py_foreground);
    else if (py_foreground != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"foreground argument must be a GdkColor or None");
	return NULL;
    }
    if (PyGdkColor_Check(py_background))
        background = PyGdkColor_Get(py_background);
    else if (py_background != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"background argument must be a GdkColor or None");
	return NULL;
    }
    text = gtk_plot_put_text(GTK_PLOT(PyGtk_Get(obj)), x, y, fontname, height,
			     angle, foreground, background, transparent,
			     justification, string);
    return pygtkextra_plot_text_new(text);
}

static PyObject *
_wrap_gtk_plot_remove_text(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *text;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_remove_text", &PyGtk_Type, &obj,
			  &text))
        return NULL;
    if (!PyGtkPlotText_Check(text)) {
        PyErr_SetString(PyExc_TypeError,
			"text argument must be a GtkPlotText");
	return NULL;
    }
    return PyInt_FromLong(gtk_plot_remove_text(GTK_PLOT(PyGtk_Get(obj)),
					       PyGtkPlotText_Get(text)));
}

static PyObject *
_wrap_gtk_plot_draw_line(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int line_style;
    float line_width;
    double x1, y1, x2, y2;
    PyObject *py_line_color;
    GtkPlotLine line;

    if (!PyArg_ParseTuple(args, "O!(ifO!)dddd:gtk_plot_draw_line",
			  &PyGtk_Type, &obj, &line_style, &line_width,
			  &PyGdkColor_Type, &py_line_color,
			  &x1, &y1, &x2, &y2))
        return NULL;
    line.line_style = line_style;
    line.line_width = line_width;
    line.color = *PyGdkColor_Get(py_line_color);
    gtk_plot_draw_line(GTK_PLOT(PyGtk_Get(obj)), line, x1, y1, x2, y2);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_draw_text(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *text;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_draw_text", &PyGtk_Type, &obj,
			  &text))
        return NULL;
    if (!PyGtkPlotText_Check(text)) {
        PyErr_SetString(PyExc_TypeError,
			"text argument must be a GtkPlotText");
	return NULL;
    }
    gtk_plot_draw_text(GTK_PLOT(PyGtk_Get(obj)), *PyGtkPlotText_Get(text));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_axis_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int axis;
    gfloat width;
    GdkColor color;

    if (!PyArg_ParseTuple(args, "O!i:gtk_plot_axis_get_attributes",
			  &PyGtk_Type, &obj, &axis))
        return NULL;
    gtk_plot_axis_get_attributes(GTK_PLOT(PyGtk_Get(obj)), axis, &width,
				 &color);
    return Py_BuildValue("(dN)", (double) width, PyGdkColor_New(&color));
}

static PyObject *
_wrap_gtk_plot_grids_visible(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gboolean vmajor, vminor, hmajor, hminor;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_grids_visible",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_grids_visible(GTK_PLOT(PyGtk_Get(obj)), &vmajor, &vminor,
			   &hmajor, &hminor);
    return Py_BuildValue("(iiii)", (int) vmajor, (int) vminor, (int) hmajor,
			 (int) hminor);
}

static PyObject *
_wrap_gtk_plot_legends_get_position(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gdouble x, y;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_legends_get_position",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot_legends_get_position(GTK_PLOT(PyGtk_Get(obj)), &x, &y);
    return Py_BuildValue("(dd)", (double) x, (double) y);
}

static PyObject *
_wrap_gtk_plot_legends_get_allocation(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkAllocation allocation;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_legends_get_allocation",
			  &PyGtk_Type, &obj))
        return NULL;
    allocation = gtk_plot_legends_get_allocation(GTK_PLOT(PyGtk_Get(obj)));
    return Py_BuildValue("(iiii)", (int) allocation.x, (int) allocation.y,
			 (int) allocation.width, (int) allocation.height);
}

static PyObject *
_wrap_gtk_plot_set_line_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int line_style;
    float line_width;
    PyObject *py_line_color;
    GtkPlotLine line;

    if (!PyArg_ParseTuple(args, "O!(ifO!):gtk_plot_set_line_attributes",
			  &PyGtk_Type, &obj, &line_style, &line_width,
			  &PyGdkColor_Type, &py_line_color))
        return NULL;
    line.line_style = line_style;
    line.line_width = line_width;
    line.color = *PyGdkColor_Get(py_line_color);
    gtk_plot_set_line_attributes(GTK_PLOT(PyGtk_Get(obj)), line);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_add_data(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *data;

    if (!PyArg_ParseTuple(args, "O!O!:gtk_plot_add_data",
			  &PyGtk_Type, &obj, &PyGtk_Type, &data))
	return NULL;
    gtk_plot_add_data(GTK_PLOT(PyGtk_Get(obj)),
		      GTK_PLOT_DATA(PyGtk_Get(data)));
    pygtkextra_plot_register_plot_data(GTK_PLOT(PyGtk_Get(obj)), data);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_remove_data(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *data;
    gint ok;

    if (!PyArg_ParseTuple(args, "O!O!:gtk_plot_remove_data",
			  &PyGtk_Type, &obj, &PyGtk_Type, &data))
        return NULL;
    ok = gtk_plot_remove_data(GTK_PLOT(PyGtk_Get(obj)),
			      GTK_PLOT_DATA(PyGtk_Get(data)));
    if (ok)
	pygtkextra_plot_unregister_plot_data(GTK_PLOT(PyGtk_Get(obj)), data);
    return PyInt_FromLong(ok);
}

static PyObject *
_wrap_gtk_plot_add_function(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *function, *extra = NULL;
    GtkPlotData *data;

    if (!PyArg_ParseTuple(args, "O!O|O!:gtk_plot_add_function",
			  &PyGtk_Type, &obj, &function, &PyTuple_Type, &extra))
        return NULL;
    if (PyCallable_Check(function)) {
	data = gtk_plot_add_function(GTK_PLOT(PyGtk_Get(obj)),
				     pygtkextra_plot_data_call_plot_function);
	if (data)
	    pygtkextra_plot_data_register_plot_function(data, function, extra);
    } else if (PyCObject_Check(function)) {
	if (extra && PyTuple_Size(extra) > 0) {
	    PyErr_SetString(PyExc_TypeError,
			    "cannot pass extra arguments to C function");
	    return NULL;
	}
	data = gtk_plot_add_function(GTK_PLOT(PyGtk_Get(obj)), (GtkPlotFunc)
				     PyCObject_AsVoidPtr(function));
    } else {
        PyErr_SetString(PyExc_TypeError, "function argument must be callable");
        return NULL;
    }
    if (!data) {
	PyErr_SetString(PyExc_RuntimeError, "cannot add plot function");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(data), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_plot_data_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(data));
}

static PyObject *
_wrap_gtk_plot_export_ps(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename, *locale;
    int orientation, eps, paper_size;

    if (!PyArg_ParseTuple(args, "O!siii:gtk_plot_export_ps",
			  &PyGtk_Type, &obj, &filename, &orientation,
			  &eps, &paper_size))
        return NULL;
    /* Since the export function crashes if the export file cannot be
       opened for writing, we have to check if it is possible to create
       the file. */
    if (pygtkextra_try_fopen(filename, "w") < 0)
	return NULL;
    locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    gtk_plot_export_ps(GTK_PLOT(PyGtk_Get(obj)), filename, orientation, eps,
		       paper_size);
    setlocale(LC_NUMERIC, locale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_export_ps_with_size(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename, *locale;
    int orientation, eps, units, width, height;

    if (!PyArg_ParseTuple(args, "O!siiiii:gtk_plot_export_ps_with_size",
			  &PyGtk_Type, &obj, &filename, &orientation,
			  &eps, &units, &width, &height))
        return NULL;
    /* Since the export function crashes if the export file cannot be
       opened for writing, we have to check if it is possible to create
       the file. */
    if (pygtkextra_try_fopen(filename, "w") < 0)
	return NULL;
    locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    gtk_plot_export_ps_with_size(GTK_PLOT(PyGtk_Get(obj)), filename,
				 orientation, eps, units, width, height);
    setlocale(LC_NUMERIC, locale);
    Py_INCREF(Py_None);
    return Py_None;
}

/* wrapper for the signals "moved" and "resized" */
static PyObject *
_gtk_plot_callback_wrapper(PyObject *self, PyObject *args)
{
    int len;
    PyObject *tuple, *ret;
    double *xp = NULL, *yp = NULL;
    PyObject *x, *y;

    len = PyTuple_Size(args) - 1;
    tuple = PyTuple_GetSlice(args, 0, len);
    if (!tuple)
	return NULL;
    x = PyTuple_GetItem(tuple, 1);
    y = PyTuple_GetItem(tuple, 2);
    if (PyCObject_Check(x) && PyCObject_Check(y)) {
	xp = (double *) PyCObject_AsVoidPtr(x);
	yp = (double *) PyCObject_AsVoidPtr(y);
	if (xp && yp) {
	    x = PyFloat_FromDouble(*xp);
	    if (x)
		PyTuple_SetItem(tuple, 1, x);
	    y = PyFloat_FromDouble(*yp);
	    if (y)
		PyTuple_SetItem(tuple, 2, y);
	}
    }
    ret = PyEval_CallObject(PyTuple_GetItem(args, len), tuple);
    Py_DECREF(tuple);
    if (PySequence_Check(ret)) {
	if (PySequence_Length(ret) == 2) {
	    x = PySequence_GetItem(ret, 0);
	    y = PySequence_GetItem(ret, 1);
	    if (x && PyNumber_Check(x) && y && PyNumber_Check(y)) {
		PyObject *fx, *fy;

		fx = PyNumber_Float(x);
		fy = PyNumber_Float(y);
		if (fx && fy) {
		    if (xp && yp) {
			*xp = PyFloat_AS_DOUBLE(fx);
			*yp = PyFloat_AS_DOUBLE(fy);
			Py_DECREF(ret);
			ret = PyInt_FromLong(1);
		    } else {
			PyErr_SetString(PyExc_RuntimeError,
					"cannot set x and y");
			Py_DECREF(ret);
			ret = NULL;
		    }
		}
		Py_XDECREF(fx);
		Py_XDECREF(fy);
	    }
	    Py_XDECREF(x);
	    Py_XDECREF(y);
	}
    }
    return ret;
}


/*
 * GtkPlotPolar
 */

static PyObject *
_wrap_gtk_plot_polar_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *py_drawable = Py_None;
    PyObject *py_width = Py_None, *py_height = Py_None;
    GdkDrawable *drawable = NULL;

    if (!PyArg_ParseTuple(args, "|OOO:gtk_plot_polar_new", &py_drawable,
			  &py_width, &py_height))
        return NULL;
    if (PyGdkWindow_Check(py_drawable))
        drawable = PyGdkWindow_Get(py_drawable);
    else if (py_drawable != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"drawable argument must be a GdkDrawable or None");
	return NULL;
    }
    if (py_width == Py_None && py_height == Py_None) {
	widget = gtk_plot_polar_new(drawable);
    } else {
	PyObject *value;
	double width, height;

	if (PyNumber_Check(py_width)
	    && (value = PyNumber_Float(py_width))) {
	    width = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "width argument must be a number");
	    return NULL;
	}
	
	if (PyNumber_Check(py_height)
	    && (value = PyNumber_Float(py_height))) {
	    height = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "height argument must be a number");
	    return NULL;
	}
	
	widget = gtk_plot_polar_new_with_size(drawable, width, height);
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlotPolar object");
	return NULL;
    }
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkPlot3D
 */

static PyObject *
_wrap_gtk_plot3d_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    PyObject *py_drawable = Py_None;
    PyObject *py_width = Py_None, *py_height = Py_None;
    GdkDrawable *drawable = NULL;

    if (!PyArg_ParseTuple(args, "|OOO:gtk_plot3d_new", &py_drawable,
			  &py_width, &py_height))
        return NULL;
    if (PyGdkWindow_Check(py_drawable))
        drawable = PyGdkWindow_Get(py_drawable);
    else if (py_drawable != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"drawable argument must be a GdkDrawable or None");
	return NULL;
    }
    if (py_width == Py_None && py_height == Py_None) {
	widget = gtk_plot3d_new(drawable);
    } else {
	PyObject *value;
	double width, height;

	if (PyNumber_Check(py_width)
	    && (value = PyNumber_Float(py_width))) {
	    width = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "width argument must be a number");
	    return NULL;
	}
	
	if (PyNumber_Check(py_height)
	    && (value = PyNumber_Float(py_height))) {
	    height = PyFloat_AS_DOUBLE(value);
	    Py_DECREF(value);
	} else {
	    PyErr_SetString(PyExc_TypeError,
			    "height argument must be a number");
	    return NULL;
	}
	
	widget = gtk_plot3d_new_with_size(drawable, width, height);
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkPlot3D object");
	return NULL;
    }
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_plot3d_rotate_vector(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x, y, z, a1, a2, a3;
    GtkPlotVector vector;

    if (!PyArg_ParseTuple(args, "O!(ddd)ddd:gtk_plot3d_rotate_vector",
			  &PyGtk_Type, &obj, &x, &y, &z, &a1, &a2, &a3))
        return NULL;
    vector.x = x;
    vector.y = y;
    vector.z = z;
    gtk_plot3d_rotate_vector(GTK_PLOT3D(PyGtk_Get(obj)), &vector, a1, a2, a3);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot3d_get_pixel(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x, y, z;
    gdouble px, py, pz;

    if (!PyArg_ParseTuple(args, "O!(ddd)ddd:gtk_plot3d_get_pixel",
			  &PyGtk_Type, &obj, &x, &y, &z))
        return NULL;
    gtk_plot3d_get_pixel(GTK_PLOT3D(PyGtk_Get(obj)), x, y, z, &px, &py, &pz);
    return Py_BuildValue("(ddd)", (double) px, (double) py, (double) pz);
}

static PyObject *
_wrap_gtk_plot3d_corner_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotLineStyle line_style;
    gfloat line_width;
    GdkColor line_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_corner_get_attributes",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_corner_get_attributes(GTK_PLOT3D(PyGtk_Get(obj)), &line_style,
				     &line_width, &line_color);
    return pygtkextra_plot_line_new(line_style, line_width, &line_color);
}

static PyObject *
_wrap_gtk_plot3d_frame_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotLineStyle line_style;
    gfloat line_width;
    GdkColor line_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_frame_get_attributes",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_frame_get_attributes(GTK_PLOT3D(PyGtk_Get(obj)), &line_style,
				    &line_width, &line_color);
    return pygtkextra_plot_line_new(line_style, line_width, &line_color);
}

static PyObject *
_wrap_gtk_plot3d_major_grids_visible(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gboolean x, y, z;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_major_grids_visible",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_major_grids_visible(GTK_PLOT3D(PyGtk_Get(obj)), &x, &y, &z);
    return Py_BuildValue("(iii)", (int) x, (int) y, (int) z);
}

static PyObject *
_wrap_gtk_plot3d_minor_grids_visible(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gboolean x, y, z;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_minor_grids_visible",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_minor_grids_visible(GTK_PLOT3D(PyGtk_Get(obj)), &x, &y, &z);
    return Py_BuildValue("(iii)", (int) x, (int) y, (int) z);
}

static PyObject *
_wrap_gtk_plot3d_major_zgrid_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotLineStyle line_style;
    gfloat line_width;
    GdkColor line_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_major_zgrid_get_attributes",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_major_zgrid_get_attributes(GTK_PLOT3D(PyGtk_Get(obj)),
					  &line_style, &line_width,
					  &line_color);
    return pygtkextra_plot_line_new(line_style, line_width, &line_color);
}

static PyObject *
_wrap_gtk_plot3d_minor_zgrid_get_attributes(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotLineStyle line_style;
    gfloat line_width;
    GdkColor line_color;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot3d_minor_zgrid_get_attributes",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_plot3d_minor_zgrid_get_attributes(GTK_PLOT3D(PyGtk_Get(obj)),
					  &line_style, &line_width,
					  &line_color);
    return pygtkextra_plot_line_new(line_style, line_width, &line_color);
}


/*
 * GtkPlotCanvas
 */

static PyObject *
_wrap_gtk_plot_canvas_get_active_plot(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlot *plot;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_canvas_get_active_plot",
			  &PyGtk_Type, &obj))
        return NULL;
    plot = gtk_plot_canvas_get_active_plot(GTK_PLOT_CANVAS(PyGtk_Get(obj)));
    if (plot)
	return PyGtk_New(GTK_OBJECT(plot));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_get_active_data(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotData *data;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_canvas_get_active_data",
			  &PyGtk_Type, &obj))
        return NULL;
    data = gtk_plot_canvas_get_active_data(GTK_PLOT_CANVAS(PyGtk_Get(obj)));
    if (data)
	return PyGtk_New(GTK_OBJECT(data));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_get_active_point(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gint active_point;
    gdouble x, y;
    GtkPlotCanvas *canvas;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_canvas_get_active_point",
			  &PyGtk_Type, &obj))
        return NULL;
    /*
    active_point =
	gtk_plot_canvas_get_active_point(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
					 &x, &y);
    */
    canvas = GTK_PLOT_CANVAS(PyGtk_Get(obj));
    active_point = canvas->active_point;
    if (active_point < 0) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    x = canvas->active_data->x[active_point];
    y = canvas->active_data->y[active_point];
    return Py_BuildValue("(idd)", (int) active_point, (double) x, (double) y);
}

static PyObject *
_wrap_gtk_plot_canvas_get_active_item(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!:gtk_plot_canvas_get_active_item",
			  &PyGtk_Type, &obj))
        return NULL;
    child = gtk_plot_canvas_get_active_item(GTK_PLOT_CANVAS(PyGtk_Get(obj)));
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_get_pixel(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x, y;
    gint ix, iy;

    if (!PyArg_ParseTuple(args, "O!dd:gtk_plot_canvas_get_pixel",
			  &PyGtk_Type, &obj, &x, &y))
        return NULL;
    gtk_plot_canvas_get_pixel(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
			      x, y, &ix, &iy);
    return Py_BuildValue("(ii)", (int) ix, (int) iy);
}

static PyObject *
_wrap_gtk_plot_canvas_get_position(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int ix, iy;
    gdouble x, y;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_plot_canvas_get_position",
			  &PyGtk_Type, &obj, &ix, &iy))
        return NULL;
    gtk_plot_canvas_get_position(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
				 ix, iy, &x, &y);
    return Py_BuildValue("(dd)", (double) x, (double) y);
}

static PyObject *
_wrap_gtk_plot_canvas_put_text(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *fontname, *string;
    PyObject *py_foreground, *py_background;
    GdkColor *foreground = NULL, *background = NULL;
    double x, y;
    int angle, height, transparent, justification;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!ddziiOOiiz:gtk_plot_canvas_put_text",
			  &PyGtk_Type, &obj, &x, &y, &fontname, &height,
			  &angle, &py_foreground, &py_background,
			  &transparent, &justification, &string))
        return NULL;
    if (PyGdkColor_Check(py_foreground))
        foreground = PyGdkColor_Get(py_foreground);
    else if (py_foreground != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"foreground argument must be a GdkColor or None");
	return NULL;
    }
    if (PyGdkColor_Check(py_background))
        background = PyGdkColor_Get(py_background);
    else if (py_background != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"background argument must be a GdkColor or None");
	return NULL;
    }
    child = gtk_plot_canvas_put_text(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
				     x, y, fontname, height, angle, foreground,
				     background, transparent, justification,
				     string);
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_put_line(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x1, y1, x2, y2;
    int line_style, arrow_mask;
    float width;
    PyObject *py_color;
    GdkColor *color = NULL;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!ddddifOi:gtk_plot_canvas_put_line",
			  &PyGtk_Type, &obj, &x1, &y1, &x2, &y2, &line_style,
			  &width, &py_color, &arrow_mask))
        return NULL;
    if (PyGdkColor_Check(py_color))
        color = PyGdkColor_Get(py_color);
    else if (py_color != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"color argument must be a GdkColor or None");
	return NULL;
    }
    child = gtk_plot_canvas_put_line(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
				     x1, y1, x2, y2, line_style, width, color,
				     arrow_mask);
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_put_rectangle(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x1, y1, x2, y2;
    int line_style, border_style, fill;
    float width;
    PyObject *py_foreground, *py_background;
    GdkColor *foreground = NULL, *background = NULL;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!ddddifOOii:gtk_plot_canvas_put_rectangle",
			  &PyGtk_Type, &obj, &x1, &y1, &x2, &y2, &line_style,
			  &width, &py_foreground, &py_background,
			  &border_style, &fill))
        return NULL;
    if (PyGdkColor_Check(py_foreground))
        foreground = PyGdkColor_Get(py_foreground);
    else if (py_foreground != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"foreground argument must be a GdkColor or None");
	return NULL;
    }
    if (PyGdkColor_Check(py_background))
        background = PyGdkColor_Get(py_background);
    else if (py_background != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"background argument must be a GdkColor or None");
	return NULL;
    }
    child = gtk_plot_canvas_put_rectangle(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
					  x1, y1, x2, y2, line_style, width,
					  foreground, background, border_style,
					  fill);
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_put_ellipse(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x1, y1, x2, y2;
    int line_style, fill;
    float width;
    PyObject *py_foreground, *py_background;
    GdkColor *foreground = NULL, *background = NULL;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!ddddifOOi:gtk_plot_canvas_put_ellipse",
			  &PyGtk_Type, &obj, &x1, &y1, &x2, &y2, &line_style,
			  &width, &py_foreground, &py_background, &fill))
        return NULL;
    if (PyGdkColor_Check(py_foreground))
        foreground = PyGdkColor_Get(py_foreground);
    else if (py_foreground != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"foreground argument must be a GdkColor or None");
	return NULL;
    }
    if (PyGdkColor_Check(py_background))
        background = PyGdkColor_Get(py_background);
    else if (py_background != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"background argument must be a GdkColor or None");
	return NULL;
    }
    child = gtk_plot_canvas_put_ellipse(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
					x1, y1, x2, y2, line_style, width,
					foreground, background, fill);
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_put_pixmap(PyObject *self, PyObject *args)
{
    PyObject *obj;
    double x1, y1;
    PyObject *py_pixmap;
    GdkPixmap *pixmap = NULL;
    GtkPlotCanvasChild *child;

    if (!PyArg_ParseTuple(args, "O!Odd:gtk_plot_canvas_put_pixmap",
			  &PyGtk_Type, &obj, py_pixmap, &x1, &y1))
        return NULL;
    if (PyGdkWindow_Check(py_pixmap))
	pixmap = PyGdkWindow_Get(py_pixmap);
    else if (py_pixmap != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"pixmap argument must be a GdkPixmap or None");
	return NULL;
    }
    child = gtk_plot_canvas_put_pixmap(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
				       pixmap, x1, y1);
    return pygtkextra_plot_canvas_child_new(child);
}

static PyObject *
_wrap_gtk_plot_canvas_put_child(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *child;
    double x1, y1, x2, y2;

    if (!PyArg_ParseTuple(args, "O!Odddd:gtk_plot_canvas_put_child",
			  &PyGtk_Type, &obj, &child, &x1, &y1, &x2, &y2))
        return NULL;
    if (!PyGtkPlotCanvasChild_Check(child)) {
        PyErr_SetString(PyExc_TypeError,
			"child argument must be a GtkPlotCanvasChild");
	return NULL;
    }
    gtk_plot_canvas_put_child(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
			      PyGtkPlotCanvasChild_Get(child),
			      x1, y1, x2, y2);
    pygtkextra_plot_canvas_register_child(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
					  child);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_child_move(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *child;
    double x1, y1;

    if (!PyArg_ParseTuple(args, "O!Odd:gtk_plot_canvas_child_move",
			  &PyGtk_Type, &obj, &child, &x1, &y1))
        return NULL;
    if (!PyGtkPlotCanvasChild_Check(child)) {
        PyErr_SetString(PyExc_TypeError,
			"child argument must be a GtkPlotCanvasChild");
	return NULL;
    }
    gtk_plot_canvas_child_move(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
			       PyGtkPlotCanvasChild_Get(child), x1, y1);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_child_move_resize(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *child;
    double x1, y1, x2, y2;

    if (!PyArg_ParseTuple(args, "O!Odddd:gtk_plot_canvas_move_resize",
			  &PyGtk_Type, &obj, &child, &x1, &y1, &x2, &y2))
        return NULL;
    if (!PyGtkPlotCanvasChild_Check(child)) {
        PyErr_SetString(PyExc_TypeError,
			"child argument must be a GtkPlotCanvasChild");
	return NULL;
    }
    gtk_plot_canvas_put_child(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
			      PyGtkPlotCanvasChild_Get(child),
			      x1, y1, x2, y2);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_remove_child(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *child;
    gboolean ok;

    if (!PyArg_ParseTuple(args, "O!O:gtk_plot_canvas_remove_child",
			  &PyGtk_Type, &obj, &child))
        return NULL;
    if (!PyGtkPlotCanvasChild_Check(child)) {
        PyErr_SetString(PyExc_TypeError,
			"child argument must be a GtkPlotCanvasChild");
	return NULL;
    }
    ok = gtk_plot_canvas_remove_child(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
				      PyGtkPlotCanvasChild_Get(child));
    if (ok)
	pygtkextra_plot_canvas_unregister_child(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
						child);
    return PyInt_FromLong(ok);
}

static PyObject *
_wrap_gtk_plot_canvas_export_ps(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename, *locale;
    int orientation, eps, paper_size;

    if (!PyArg_ParseTuple(args, "O!siii:gtk_plot_canvas_export_ps",
			  &PyGtk_Type, &obj, &filename, &orientation,
			  &eps, &paper_size))
        return NULL;
    /* Since the export function crashes if the export file cannot be
       opened for writing, we have to check if it is possible to create
       the file. */
    if (pygtkextra_try_fopen(filename, "w") < 0)
	return NULL;
    locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    gtk_plot_canvas_export_ps(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
			      filename, orientation, eps, paper_size);
    setlocale(LC_NUMERIC, locale);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_plot_canvas_export_ps_with_size(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename, *locale;
    int orientation, eps, units, width, height;

    if (!PyArg_ParseTuple(args, "O!siiiii:gtk_plot_canvas_export_ps_with_size",
			  &PyGtk_Type, &obj, &filename, &orientation,
			  &eps, &units, &width, &height))
        return NULL;
    /* Since the export function crashes if the export file cannot be
       opened for writing, we have to check if it is possible to create
       the file. */
    if (pygtkextra_try_fopen(filename, "w") < 0)
	return NULL;
    locale = setlocale(LC_NUMERIC, NULL);
    setlocale(LC_NUMERIC, "C");
    gtk_plot_canvas_export_ps_with_size(GTK_PLOT_CANVAS(PyGtk_Get(obj)),
					filename, orientation, eps, units,
					width, height);
    setlocale(LC_NUMERIC, locale);
    Py_INCREF(Py_None);
    return Py_None;
}


/*
 * GtkIconList
 */

static PyObject *
_wrap_gtk_icon_list_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    int icon_width = 48, mode = GTK_ICON_LIST_TEXT_BELOW;

    if (!PyArg_ParseTuple(args, "|ii:gtk_icon_list_new", &icon_width, &mode))
        return NULL;
    widget = gtk_icon_list_new(icon_width, mode);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkIconList object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_icon_list_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_icon_list_add_from_pixmap(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *label = NULL;
    PyObject *py_pixmap, *py_mask = Py_None, *object = Py_None;
    GdkBitmap *mask = NULL;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O|OzO:gtk_icon_list_add_from_pixmap",
			  &PyGtk_Type, &obj, &py_pixmap, &py_mask, &label, &object))
        return NULL;
    if (!PyGdkWindow_Check(py_pixmap)) {
        PyErr_SetString(PyExc_TypeError, "pixmap argument must be a GdkPixmap");
	return NULL;
    }
    if (PyGdkWindow_Check(py_mask))
        mask = PyGdkWindow_Get(py_mask);
    else if (py_mask != Py_None) {
        PyErr_SetString(PyExc_TypeError,
			"mask argument must be a GdkBitmap or None");
	return NULL;
    }
    item =
	gtk_icon_list_add_from_pixmap(GTK_ICON_LIST(PyGtk_Get(obj)),
				      PyGdkWindow_Get(py_pixmap), mask, label,
				      pygtkextra_icon_list_register_link(object));
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_add_from_data(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *label = NULL, **vector;
    PyObject *data, *object = Py_None;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O|zO:gtk_icon_list_add_from_data",
			  &PyGtk_Type, &obj, &data, &label, &object))
        return NULL;
    /* Convert the string list to a character array. */
    if (!(vector = pygtkextra_convert_pixmap_data_to_vector(data)))
	return NULL;
    item =
	gtk_icon_list_add_from_data(GTK_ICON_LIST(PyGtk_Get(obj)),
				    vector, label,
				    pygtkextra_icon_list_register_link(object));
    g_free(vector);
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_add(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename, *label = NULL;
    PyObject *object = Py_None;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!s|zO:gtk_icon_list_add",
			  &PyGtk_Type, &obj, &filename, &label, &object))
        return NULL;
    /* The pixmap file must exist and be readable. */
    if (pygtkextra_try_fopen(filename, "r") < 0)
	return NULL;
    item = gtk_icon_list_add(GTK_ICON_LIST(PyGtk_Get(obj)), filename, label,
			     pygtkextra_icon_list_register_link(object));
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_get_nth(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int n;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!i:gtk_icon_list_get_nth",
			  &PyGtk_Type, &obj, &n))
        return NULL;
    item = gtk_icon_list_get_nth(GTK_ICON_LIST(PyGtk_Get(obj)), n);
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_get_index(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;
    int i;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_get_index",
			  &PyGtk_Type, &obj, &py_item))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    i = gtk_icon_list_get_index(GTK_ICON_LIST(PyGtk_Get(obj)),
				PyGtkIconListItem_Get(py_item));
    return PyInt_FromLong(i);
}

static PyObject *
_wrap_gtk_icon_list_remove(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_remove",
			  &PyGtk_Type, &obj, &py_item))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    item = PyGtkIconListItem_Get(py_item);
    if (item->link)
	pygtkextra_icon_list_unregister_link(item->link);
    gtk_icon_list_remove(GTK_ICON_LIST(PyGtk_Get(obj)), item);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_set_active_icon(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_set_active_icon",
			  &PyGtk_Type, &obj, &py_item))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    item = PyGtkIconListItem_Get(py_item);
    gtk_icon_list_set_active_icon(GTK_ICON_LIST(PyGtk_Get(obj)), item);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_remove_nth(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int n;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!i:gtk_icon_list_remove_nth",
			  &PyGtk_Type, &obj, &n))
        return NULL;
    item = gtk_icon_list_get_nth(GTK_ICON_LIST(PyGtk_Get(obj)), n);
    if (item) {
	if (item->link)
	    pygtkextra_icon_list_unregister_link(item->link);
	gtk_icon_list_remove(GTK_ICON_LIST(PyGtk_Get(obj)), item);
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_clear(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_icon_list_clear", &PyGtk_Type, &obj))
        return NULL;
    pygtkextra_icon_list_unref_links(GTK_ICON_LIST(PyGtk_Get(obj)));
    gtk_icon_list_clear(GTK_ICON_LIST(PyGtk_Get(obj)));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_get_icon_from_link(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *object;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_get_icon_from_link",
			  &PyGtk_Type, &obj, &object))
        return NULL;
    item =
	gtk_icon_list_get_icon_from_link(GTK_ICON_LIST(PyGtk_Get(obj)),
					 pygtkextra_icon_list_get_link(object));
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_get_icon_at(PyObject *self, PyObject *args)
{
    PyObject *obj;
    int x, y;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!ii:gtk_icon_list_get_icon_at",
			  &PyGtk_Type, &obj, &x, &y))
        return NULL;
    item = gtk_icon_list_get_icon_at(GTK_ICON_LIST(PyGtk_Get(obj)),
				     x, y);
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_get_active_icon(PyObject *self, PyObject *args)
{
    PyObject *obj;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!:gtk_icon_list_get_active_icon",
			  &PyGtk_Type, &obj))
        return NULL;
    item = gtk_icon_list_get_active_icon(GTK_ICON_LIST(PyGtk_Get(obj)));
    return pygtkextra_icon_list_item_new(item);
}

static PyObject *
_wrap_gtk_icon_list_set_label(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;
    char *label;

    if (!PyArg_ParseTuple(args, "O!Oz:gtk_icon_list_set_label",
			  &PyGtk_Type, &obj, &py_item, &label))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    if (!label)
	label = "";
    gtk_icon_list_set_label(GTK_ICON_LIST(PyGtk_Get(obj)),
			    PyGtkIconListItem_Get(py_item), label);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_select_icon(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_select_icon",
			  &PyGtk_Type, &obj, &py_item))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    gtk_icon_list_select_icon(GTK_ICON_LIST(PyGtk_Get(obj)),
			      PyGtkIconListItem_Get(py_item));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_icon_list_unselect_icon(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *py_item;
    GtkIconListItem *item;

    if (!PyArg_ParseTuple(args, "O!O:gtk_icon_list_unselect_icon",
			  &PyGtk_Type, &obj, &py_item))
        return NULL;
    if (!PyGtkIconListItem_Check(py_item)) {
	PyErr_SetString(PyExc_TypeError,
			"item argument must be a GtkIconListItem");
	return NULL;
    }
    item = PyGtkIconListItem_Get(py_item);
    gtk_icon_list_unselect_icon(GTK_ICON_LIST(PyGtk_Get(obj)), item);
    Py_INCREF(Py_None);
    return Py_None;
}


/*
 * GtkFileList
 */

static PyObject *
_wrap_gtk_file_list_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    char *path = NULL;
    int icon_width = 20, mode = GTK_ICON_LIST_TEXT_RIGHT;

    if (!PyArg_ParseTuple(args, "|iiz:gtk_file_list_new", &icon_width, &mode,
			  &path))
        return NULL;
    widget = gtk_file_list_new(icon_width, mode, path);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkFileList object");
	return NULL;
    }
    gtk_signal_connect(GTK_OBJECT(widget), "destroy",
		       GTK_SIGNAL_FUNC(pygtkextra_icon_list_destroy_cb), NULL);
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_file_list_get_filename(PyObject *self, PyObject *args)
{
    PyObject *obj;
    char *filename;

    if (!PyArg_ParseTuple(args, "O!:gtk_file_list_get_filename",
			  &PyGtk_Type, &obj))
        return NULL;
    filename = gtk_file_list_get_filename(GTK_FILE_LIST(PyGtk_Get(obj)));
    return PyString_FromString((filename) ? filename : "");
}

static PyObject *
_wrap_gtk_file_list_add_type(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *data;
    char **vector;
    gint type;

    if (!PyArg_ParseTuple(args, "O!O:gtk_file_list_add_type",
			  &PyGtk_Type, &obj, &data))
        return NULL;
    /* Convert the string list to a character array. */
    if (!(vector = pygtkextra_convert_pixmap_data_to_vector(data)))
	return NULL;
    type = gtk_file_list_add_type(GTK_FILE_LIST(PyGtk_Get(obj)),
				  (const gchar **) vector);
    g_free(vector);
    return PyInt_FromLong(type);
}


/*
 * GtkIconFileSelection
 */

static PyObject *
_wrap_gtk_icon_file_selection_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    char *title = NULL;
    GtkWidget *file_list;

    if (!PyArg_ParseTuple(args, "|z:gtk_icon_file_selection_new", &title))
        return NULL;
    if (!title)
	title = "";
    widget = gtk_icon_file_selection_new(title);
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkIconFileSelection object");
	return NULL;
    }
    file_list = GTK_ICON_FILESEL(widget)->file_list;
    if (file_list) {
	gtk_signal_connect(GTK_OBJECT(file_list), "destroy",
			   GTK_SIGNAL_FUNC(pygtkextra_icon_list_destroy_cb),
			   NULL);
    }
    return PyGtk_New(GTK_OBJECT(widget));
}


/*
 * GtkItemEntry
 */

static PyObject *
_wrap_gtk_item_entry_get_justification(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_item_entry_get_justification",
			  &PyGtk_Type, &obj))
        return NULL;
    return PyInt_FromLong(GTK_ITEM_ENTRY(PyGtk_Get(obj))->justification);
}


/*
 * GtkColorCombo
 */

static PyObject *
_wrap_gtk_color_combo_new(PyObject *self, PyObject *args)
{
    GtkWidget *widget;
    int rows = 0, columns = 0;
    PyObject *colors = Py_None;

    /*
     * If you don't pass the number of rows and columns the size of the
     * color palette is calculated.
     */
     
    if (!PyArg_ParseTuple(args, "|iiO:gtk_color_combo_new",
			  &rows, &columns, &colors))
        return NULL;
    if (colors == Py_None) {
	widget = gtk_color_combo_new();
    } else {
	int i, len, size;
	char **vector;
	
	widget = NULL;
	if (!PySequence_Check(colors)) {
	    PyErr_SetString(PyExc_TypeError,
			    "colors argument must be a sequence");
	    return NULL;
	}
	len = PySequence_Length(colors);
	size = pygtkextra_color_combo_get_size(len, &rows, &columns);
	vector = g_new(char *, size);
	for (i = 0; i < size; ++i) {
	    if (i < len) {
		PyObject *color;
	    
		color = PySequence_GetItem(colors, i);
		vector[i] = pygtkextra_get_colorname(color);
		Py_DECREF(color);
		if (!vector[i]) {
		    PyErr_SetString(PyExc_TypeError,
				    "sequence items must be color "\
				    "specifications");
		    size = i + 1;
		    goto cleanup;
		}
	    } else
		vector[i] = g_strdup("#000000000000");
	}
    
	widget = gtk_color_combo_new_with_values(rows, columns, vector);
	
    cleanup:

	for (i = 0; i < size; ++i)
	    g_free(vector[i]);
	g_free(vector);
    }
    if (!widget) {
	PyErr_SetString(PyExc_RuntimeError,
			"cannot create GtkColorCombo object");
	return NULL;
    }
    return PyGtk_New(GTK_OBJECT(widget));
}

static PyObject *
_wrap_gtk_color_combo_find_color(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *color;
    gint row, column;

    if (!PyArg_ParseTuple(args, "O!O!:gtk_color_combo_find_color",
			  &PyGtk_Type, &obj, &PyGdkColor_Type, &color))
        return NULL;
    gtk_color_combo_find_color(GTK_COLOR_COMBO(PyGtk_Get(obj)),
			       PyGdkColor_Get(color), &row, &column);
    if (row < 0 || column < 0) {
	/* In Python the function returns None if the color was not found. */
	Py_INCREF(Py_None);
	return Py_None;
    }
    return Py_BuildValue("(ii)", (int) row, (int) column);
}


/*
 * GtkToggleCombo
 */

static PyObject *
_wrap_gtk_toggle_combo_get_selection(PyObject *self, PyObject *args)
{
    PyObject *obj;
    gint row, column;

    if (!PyArg_ParseTuple(args, "O!:gtk_toggle_combo_get_selection",
			  &PyGtk_Type, &obj))
        return NULL;
    gtk_toggle_combo_get_selection(GTK_TOGGLE_COMBO(PyGtk_Get(obj)),
				   &row, &column);
    if (row < 0 || column < 0) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    return Py_BuildValue("(ii)", (int) row, (int) column);
}


/*
 * GtkFontCombo
 */

static PyObject *
_wrap_gtk_font_combo_get_psfont(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if (!PyArg_ParseTuple(args, "O!:gtk_font_combo_get_psfont",
			  &PyGtk_Type, &obj))
        return NULL;
    return pygtkextra_psfont_new(GTK_FONT_COMBO(PyGtk_Get(obj))->psfont);
}


/*
 * GtkPSFont
 */

static PyObject *
_wrap_gtk_psfont_get_font(PyObject *self, PyObject *args)
{
    char *fontname;

    if (!PyArg_ParseTuple(args, "s:gtk_psfont_get_font", &fontname))
        return NULL;
    return pygtkextra_psfont_new(gtk_psfont_get_font(fontname));
}

static PyObject *
_wrap_gtk_psfont_get_gdkfont(PyObject *self, PyObject *args)
{
    int height;
    char *fontname;
    GdkFont *font;

    if (!PyArg_ParseTuple(args, "si:gtk_psfont_get_gdkfont", &fontname,
			  &height))
        return NULL;
    font = gtk_psfont_get_gdkfont(fontname, height);
    if (font) {
	PyObject *obj = PyGdkFont_New(font);
	gdk_font_unref(font);
	return obj;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_psfont_add_font(PyObject *self, PyObject *args)
{
    int italic, bold;
    char *fontname, *psfont, *family, *xfont[2];
    PyObject *py_xfont;

    xfont[0] = NULL;
    xfont[1] = NULL;
    if (!PyArg_ParseTuple(args, "sssOii:gtk_psfont_add_font", &fontname,
			  &psfont, &family, &py_xfont, &italic, &bold))
        return NULL;
    if (PyString_Check(py_xfont))
	xfont[0] = PyString_AS_STRING(py_xfont);
    else if (PySequence_Check(py_xfont)) {
	int i, len;
	
	len = PySequence_Length(py_xfont);
	if (len > 2) {
	    PyErr_SetString(PyExc_ValueError,
			    "sequence must have at most 2 items");
	    return NULL;
	}
	for (i = 0; i < len; ++i) {
	    PyObject *item = PySequence_GetItem(py_xfont, i);
	    if (PyString_Check(item))
		xfont[i] = PyString_AS_STRING(item);
	    else if (item != Py_None) {
		Py_DECREF(item);
		PyErr_SetString(PyExc_TypeError,
				"sequence items must be strings or None");
		return NULL;
	    }
	    Py_DECREF(item);
	}
    } else {
	PyErr_SetString(PyExc_TypeError,
			"4th argument must be sequence or string");
	return NULL;
    }
    gtk_psfont_add_font(fontname, psfont, family, xfont, italic, bold);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_psfont_add_i18n_font(PyObject *self, PyObject *args)
{
    int italic, bold, vertical;
    char *fontname, *psfont, *family, *i18n_latinfamily, *xfont[2];
    PyObject *py_xfont;

    xfont[0] = NULL;
    xfont[1] = NULL;
    if (!PyArg_ParseTuple(args, "ssssOiii:gtk_psfont_add_i18n_font", &fontname,
			  &psfont, &family, &i18n_latinfamily, &py_xfont,
			  &italic, &bold, &vertical))
        return NULL;
    if (PyString_Check(py_xfont))
	xfont[0] = PyString_AS_STRING(py_xfont);
    else if (PySequence_Check(py_xfont)) {
	int i, len;
	
	len = PySequence_Length(py_xfont);
	if (len > 2) {
	    PyErr_SetString(PyExc_ValueError,
			    "sequence must have at most 2 items");
	    return NULL;
	}
	for (i = 0; i < len; ++i) {
	    PyObject *item = PySequence_GetItem(py_xfont, i);
	    if (PyString_Check(item))
		xfont[i] = PyString_AS_STRING(item);
	    else if (item != Py_None) {
		Py_DECREF(item);
		PyErr_SetString(PyExc_TypeError,
				"sequence items must be strings or None");
		return NULL;
	    }
	    Py_DECREF(item);
	}
    } else {
	PyErr_SetString(PyExc_TypeError,
			"5th argument must be sequence or string");
	return NULL;
    }
    gtk_psfont_add_i18n_font(fontname, psfont, family, i18n_latinfamily, xfont,
			     italic, bold, vertical);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_gtk_psfont_find_by_family(PyObject *self, PyObject *args)
{
    char *family;
    int italic, bold;

    if (!PyArg_ParseTuple(args, "sii:gtk_psfont_find_by_family", &family,
			  &italic, &bold))
        return NULL;
    return pygtkextra_psfont_new(gtk_psfont_find_by_family(family, italic,
							   bold));
}

static PyObject *
_wrap_gtk_psfont_get_families(PyObject *self, PyObject *args)
{
    int i;
    gint len;
    GList *families;
    PyObject *list;
    
    if (!PyArg_ParseTuple(args, ":gtk_psfont_get_families"))
        return NULL;
    gtk_psfont_get_families(&families, &len);
    list = PyList_New(len);
    if (!list) {
	g_list_free(families);
	return NULL;
    }
    for (i = 0; i < len; ++i) {
	PyObject *family;

	family = PyString_FromString((char *) g_list_nth_data(families, i));
	if (!family) {
	    Py_DECREF(list);
	    g_list_free(families);
	    return NULL;
	}
	PyList_SET_ITEM(list, i, family);
    }
    g_list_free(families);
    return list;
}

#define GTK_ICON_FILE_SELECTION GTK_ICON_FILESEL
#define gtk_combo_box_get_type gtk_combobox_get_type
#define gtk_combo_box_new gtk_combobox_new
#define gtk_combo_box_hide_popdown_window gtk_combobox_hide_popdown_window

#include "gtkextramodule_impl.h"

static PyMethodDef _gtkextraMethods[] =
{
    { "GtkSheetRange", PyGtkSheetRange_New, 1 },
    { "GtkPlotLine", PyGtkPlotLine_New, 1 },
    { "gtk_sheet_new", _wrap_gtk_sheet_new, 1 },
    { "gtk_sheet_get_entry", _wrap_gtk_sheet_get_entry, 1 },
    { "gtk_sheet_get_entry_widget", _wrap_gtk_sheet_get_entry_widget, 1 },
    { "gtk_sheet_get_visible_range", _wrap_gtk_sheet_get_visible_range, 1 },
    { "gtk_sheet_clip_range", _wrap_gtk_sheet_clip_range, 1 },
    { "gtk_sheet_get_vadjustment", _wrap_gtk_sheet_get_vadjustment, 1 },
    { "gtk_sheet_get_hadjustment", _wrap_gtk_sheet_get_hadjustment, 1 },
    { "gtk_sheet_select_range", _wrap_gtk_sheet_select_range, 1 },
    { "gtk_sheet_get_active_cell", _wrap_gtk_sheet_get_active_cell, 1 },
    { "gtk_sheet_cell_get_text", _wrap_gtk_sheet_cell_get_text, 1 },
    { "gtk_sheet_range_clear", _wrap_gtk_sheet_range_clear, 1 },
    { "gtk_sheet_range_delete", _wrap_gtk_sheet_range_delete, 1 },
    { "gtk_sheet_link_cell", _wrap_gtk_sheet_link_cell, 1 },
    { "gtk_sheet_get_link", _wrap_gtk_sheet_get_link, 1 },
    { "gtk_sheet_remove_link", _wrap_gtk_sheet_remove_link, 1 },
    { "gtk_sheet_get_pixel_info", _wrap_gtk_sheet_get_pixel_info, 1 },
    { "gtk_sheet_get_cell_area", _wrap_gtk_sheet_get_cell_area, 1 },
    { "gtk_sheet_range_set_background", _wrap_gtk_sheet_range_set_background, 1 },
    { "gtk_sheet_range_set_foreground", _wrap_gtk_sheet_range_set_foreground, 1 },
    { "gtk_sheet_range_set_justification", _wrap_gtk_sheet_range_set_justification, 1 },
    { "gtk_sheet_range_set_editable", _wrap_gtk_sheet_range_set_editable, 1 },
    { "gtk_sheet_range_set_visible", _wrap_gtk_sheet_range_set_visible, 1 },
    { "gtk_sheet_range_set_border", _wrap_gtk_sheet_range_set_border, 1 },
    { "gtk_sheet_range_set_border_color", _wrap_gtk_sheet_range_set_border_color, 1 },
    { "gtk_sheet_range_set_font", _wrap_gtk_sheet_range_set_font, 1 },
    { "gtk_sheet_get_attributes", _wrap_gtk_sheet_get_attributes, 1 },
    { "gtk_sheet_put", _wrap_gtk_sheet_put, 1 },
    { "gtk_sheet_get_child_at", _wrap_gtk_sheet_get_child_at, 1 },
    { "gtk_sheet_get_column_title", _wrap_gtk_sheet_get_column_title, 1 },
    { "gtk_sheet_get_row_title", _wrap_gtk_sheet_get_row_title, 1 },
    { "gtk_sheet_get_column_width", _wrap_gtk_sheet_get_column_width, 1 },
    { "gtk_sheet_get_row_height", _wrap_gtk_sheet_get_row_height, 1 },
    { "gtk_sheet_get_range", _wrap_gtk_sheet_get_range, 1 },
    { "_gtk_sheet_callback_wrapper", _gtk_sheet_callback_wrapper, 1 },
    { "gtk_plot_data_new", _wrap_gtk_plot_data_new, 1 },
    { "gtk_plot_data_set_numpoints", _wrap_gtk_plot_data_set_numpoints, 1 },
    { "gtk_plot_data_set_x", _wrap_gtk_plot_data_set_x, 1 },
    { "gtk_plot_data_get_x", _wrap_gtk_plot_data_get_x, 1 },
    { "gtk_plot_data_set_y", _wrap_gtk_plot_data_set_y, 1 },
    { "gtk_plot_data_get_y", _wrap_gtk_plot_data_get_y, 1 },
    { "gtk_plot_data_set_z", _wrap_gtk_plot_data_set_z, 1 },
    { "gtk_plot_data_get_z", _wrap_gtk_plot_data_get_z, 1 },
    { "gtk_plot_data_set_a", _wrap_gtk_plot_data_set_a, 1 },
    { "gtk_plot_data_get_a", _wrap_gtk_plot_data_get_a, 1 },
    { "gtk_plot_data_set_dx", _wrap_gtk_plot_data_set_dx, 1 },
    { "gtk_plot_data_get_dx", _wrap_gtk_plot_data_get_dx, 1 },
    { "gtk_plot_data_set_dy", _wrap_gtk_plot_data_set_dy, 1 },
    { "gtk_plot_data_get_dy", _wrap_gtk_plot_data_get_dy, 1 },
    { "gtk_plot_data_set_dz", _wrap_gtk_plot_data_set_dz, 1 },
    { "gtk_plot_data_get_dz", _wrap_gtk_plot_data_get_dz, 1 },
    { "gtk_plot_data_set_da", _wrap_gtk_plot_data_set_da, 1 },
    { "gtk_plot_data_get_da", _wrap_gtk_plot_data_get_da, 1 },
    { "gtk_plot_data_set_points", _wrap_gtk_plot_data_set_points, 1 },
    { "gtk_plot_data_get_points", _wrap_gtk_plot_data_get_points, 1 },
    { "gtk_plot_data_get_point", _wrap_gtk_plot_data_get_point, 1 },
    { "gtk_plot_data_set_labels", _wrap_gtk_plot_data_set_labels, 1 },
    { "gtk_plot_data_get_labels", _wrap_gtk_plot_data_get_labels, 1 },
    { "gtk_plot_data_set_symbol", _wrap_gtk_plot_data_set_symbol, 1 },
    { "gtk_plot_data_get_symbol", _wrap_gtk_plot_data_get_symbol, 1 },
    { "gtk_plot_data_get_line_attributes", _wrap_gtk_plot_data_get_line_attributes, 1 },
    { "gtk_plot_data_get_gradient_colors", _wrap_gtk_plot_data_get_gradient_colors, 1 },
    { "gtk_plot_data_get_gradient", _wrap_gtk_plot_data_get_gradient, 1 },
    { "gtk_plot_data_get_gradient_level", _wrap_gtk_plot_data_get_gradient_level, 1 },
    { "gtk_plot_data_set_link", _wrap_gtk_plot_data_set_link, 1 },
    { "gtk_plot_data_get_link", _wrap_gtk_plot_data_get_link, 1 },
    { "gtk_plot_data_remove_link", _wrap_gtk_plot_data_remove_link, 1 },
    { "gtk_plot_data_add_marker", _wrap_gtk_plot_data_add_marker, 1 },
    { "gtk_plot_data_remove_marker", _wrap_gtk_plot_data_remove_marker, 1 },
    { "gtk_plot_bar_new", _wrap_gtk_plot_bar_new, 1 },
    { "gtk_plot_box_new", _wrap_gtk_plot_box_new, 1 },
    { "gtk_plot_flux_new", _wrap_gtk_plot_flux_new, 1 },
    { "gtk_plot_flux_get_arrow", _wrap_gtk_plot_flux_get_arrow, 1 },
    { "gtk_plot_surface_new", _wrap_gtk_plot_surface_new, 1 },
    { "gtk_plot_surface_set_points", _wrap_gtk_plot_surface_set_points, 1 },
    { "gtk_plot_surface_get_points", _wrap_gtk_plot_surface_get_points, 1 },
    { "gtk_plot_surface_set_nx", _wrap_gtk_plot_surface_set_nx, 1 },
    { "gtk_plot_surface_set_ny", _wrap_gtk_plot_surface_set_ny, 1 },
    { "gtk_plot_surface_set_x", _wrap_gtk_plot_surface_set_x, 1 },
    { "gtk_plot_surface_set_y", _wrap_gtk_plot_surface_set_y, 1 },
    { "gtk_plot_surface_set_z", _wrap_gtk_plot_surface_set_z, 1 },
    { "gtk_plot_surface_set_dx", _wrap_gtk_plot_surface_set_dx, 1 },
    { "gtk_plot_surface_set_dy", _wrap_gtk_plot_surface_set_dy, 1 },
    { "gtk_plot_surface_set_dz", _wrap_gtk_plot_surface_set_dz, 1 },
    { "gtk_plot_surface_get_x", _wrap_gtk_plot_surface_get_x, 1 },
    { "gtk_plot_surface_get_y", _wrap_gtk_plot_surface_get_y, 1 },
    { "gtk_plot_surface_get_z", _wrap_gtk_plot_surface_get_z, 1 },
    { "gtk_plot_surface_get_dx", _wrap_gtk_plot_surface_get_dx, 1 },
    { "gtk_plot_surface_get_dy", _wrap_gtk_plot_surface_get_dy, 1 },
    { "gtk_plot_surface_get_dz", _wrap_gtk_plot_surface_get_dz, 1 },
    { "gtk_plot_csurface_new", _wrap_gtk_plot_csurface_new, 1 },
    { "gtk_plot_pixmap_new", _wrap_gtk_plot_pixmap_new, 1 },
    { "gtk_plot_new", _wrap_gtk_plot_new, 1 },
    { "gtk_plot_get_position", _wrap_gtk_plot_get_position, 1 },
    { "gtk_plot_get_size", _wrap_gtk_plot_get_size, 1 },
    { "gtk_plot_get_internal_allocation", _wrap_gtk_plot_get_internal_allocation, 1 },
    { "gtk_plot_refresh", _wrap_gtk_plot_refresh, 1 },
    { "gtk_plot_get_pixel", _wrap_gtk_plot_get_pixel, 1 },
    { "gtk_plot_get_point", _wrap_gtk_plot_get_point, 1 },
    { "gtk_plot_get_xrange", _wrap_gtk_plot_get_xrange, 1 },
    { "gtk_plot_get_yrange", _wrap_gtk_plot_get_yrange, 1 },
    { "gtk_plot_put_text", _wrap_gtk_plot_put_text, 1 },
    { "gtk_plot_remove_text", _wrap_gtk_plot_remove_text, 1 },
    { "gtk_plot_draw_line", _wrap_gtk_plot_draw_line, 1 },
    { "gtk_plot_draw_text", _wrap_gtk_plot_draw_text, 1 },
    { "gtk_plot_axis_get_attributes", _wrap_gtk_plot_axis_get_attributes, 1 },
    { "gtk_plot_grids_visible", _wrap_gtk_plot_grids_visible, 1 },
    { "gtk_plot_legends_get_position", _wrap_gtk_plot_legends_get_position, 1 },
    { "gtk_plot_legends_get_allocation", _wrap_gtk_plot_legends_get_allocation, 1 },
    { "gtk_plot_set_line_attributes", _wrap_gtk_plot_set_line_attributes, 1 },
    { "gtk_plot_add_data", _wrap_gtk_plot_add_data, 1 },
    { "gtk_plot_remove_data", _wrap_gtk_plot_remove_data, 1 },
    { "gtk_plot_add_function", _wrap_gtk_plot_add_function, 1 },
    { "gtk_plot_export_ps", _wrap_gtk_plot_export_ps, 1 },
    { "gtk_plot_export_ps_with_size", _wrap_gtk_plot_export_ps_with_size, 1 },
    { "_gtk_plot_callback_wrapper", _gtk_plot_callback_wrapper, 1 },
    { "gtk_plot_polar_new", _wrap_gtk_plot_polar_new, 1 },
    { "gtk_plot3d_new", _wrap_gtk_plot3d_new, 1 },
    { "gtk_plot3d_rotate_vector", _wrap_gtk_plot3d_rotate_vector, 1 },
    { "gtk_plot3d_get_pixel", _wrap_gtk_plot3d_get_pixel, 1 },
    { "gtk_plot3d_corner_get_attributes", _wrap_gtk_plot3d_corner_get_attributes, 1 },
    { "gtk_plot3d_frame_get_attributes", _wrap_gtk_plot3d_frame_get_attributes, 1 },
    { "gtk_plot3d_major_grids_visible", _wrap_gtk_plot3d_major_grids_visible, 1 },
    { "gtk_plot3d_minor_grids_visible", _wrap_gtk_plot3d_minor_grids_visible, 1 },
    { "gtk_plot3d_major_zgrid_get_attributes", _wrap_gtk_plot3d_major_zgrid_get_attributes, 1 },
    { "gtk_plot3d_minor_zgrid_get_attributes", _wrap_gtk_plot3d_minor_zgrid_get_attributes, 1 },
    { "gtk_plot_canvas_get_active_plot", _wrap_gtk_plot_canvas_get_active_plot, 1 },
    { "gtk_plot_canvas_get_active_data", _wrap_gtk_plot_canvas_get_active_data, 1 },
    { "gtk_plot_canvas_get_active_point", _wrap_gtk_plot_canvas_get_active_point, 1 },
    { "gtk_plot_canvas_get_active_item", _wrap_gtk_plot_canvas_get_active_item, 1 },
    { "gtk_plot_canvas_get_pixel", _wrap_gtk_plot_canvas_get_pixel, 1 },
    { "gtk_plot_canvas_get_position", _wrap_gtk_plot_canvas_get_position, 1 },
    { "gtk_plot_canvas_put_text", _wrap_gtk_plot_canvas_put_text, 1 },
    { "gtk_plot_canvas_put_line", _wrap_gtk_plot_canvas_put_line, 1 },
    { "gtk_plot_canvas_put_rectangle", _wrap_gtk_plot_canvas_put_rectangle, 1 },
    { "gtk_plot_canvas_put_ellipse", _wrap_gtk_plot_canvas_put_ellipse, 1 },
    { "gtk_plot_canvas_put_pixmap", _wrap_gtk_plot_canvas_put_pixmap, 1 },
    { "gtk_plot_canvas_put_child", _wrap_gtk_plot_canvas_put_child, 1 },
    { "gtk_plot_canvas_child_move", _wrap_gtk_plot_canvas_child_move, 1 },
    { "gtk_plot_canvas_child_move_resize", _wrap_gtk_plot_canvas_child_move_resize, 1 },
    { "gtk_plot_canvas_remove_child", _wrap_gtk_plot_canvas_remove_child, 1 },
    { "gtk_plot_canvas_export_ps", _wrap_gtk_plot_canvas_export_ps, 1 },
    { "gtk_plot_canvas_export_ps_with_size", _wrap_gtk_plot_canvas_export_ps_with_size, 1 },
    { "gtk_icon_list_new", _wrap_gtk_icon_list_new, 1 },
    { "gtk_icon_list_add_from_pixmap", _wrap_gtk_icon_list_add_from_pixmap, 1 },
    { "gtk_icon_list_add_from_data", _wrap_gtk_icon_list_add_from_data, 1 },
    { "gtk_icon_list_add", _wrap_gtk_icon_list_add, 1 },
    { "gtk_icon_list_get_nth", _wrap_gtk_icon_list_get_nth, 1 },
    { "gtk_icon_list_get_index", _wrap_gtk_icon_list_get_index, 1 },
    { "gtk_icon_list_remove", _wrap_gtk_icon_list_remove, 1 },
    { "gtk_icon_list_set_active_icon", _wrap_gtk_icon_list_set_active_icon, 1 },
    { "gtk_icon_list_remove_nth", _wrap_gtk_icon_list_remove_nth, 1 },
    { "gtk_icon_list_clear", _wrap_gtk_icon_list_clear, 1 },
    { "gtk_icon_list_get_icon_from_link", _wrap_gtk_icon_list_get_icon_from_link, 1 },
    { "gtk_icon_list_get_icon_at", _wrap_gtk_icon_list_get_icon_at, 1 },
    { "gtk_icon_list_get_active_icon", _wrap_gtk_icon_list_get_active_icon, 1 },
    { "gtk_icon_list_set_label", _wrap_gtk_icon_list_set_label, 1 },
    { "gtk_icon_list_select_icon", _wrap_gtk_icon_list_select_icon, 1 },
    { "gtk_icon_list_unselect_icon", _wrap_gtk_icon_list_unselect_icon, 1 },
    { "gtk_file_list_new", _wrap_gtk_file_list_new, 1 },
    { "gtk_file_list_get_filename", _wrap_gtk_file_list_get_filename, 1 },
    { "gtk_file_list_add_type", _wrap_gtk_file_list_add_type, 1 },
    { "gtk_icon_file_selection_new", _wrap_gtk_icon_file_selection_new, 1 },
    { "gtk_item_entry_get_justification", _wrap_gtk_item_entry_get_justification, 1 },
    { "gtk_color_combo_new", _wrap_gtk_color_combo_new, 1 },
    { "gtk_color_combo_find_color", _wrap_gtk_color_combo_find_color, 1 },
    { "gtk_toggle_combo_get_selection", _wrap_gtk_toggle_combo_get_selection, 1 },
    { "gtk_font_combo_get_psfont", _wrap_gtk_font_combo_get_psfont, 1 },
    { "gtk_psfont_get_font", _wrap_gtk_psfont_get_font, 1 },
    { "gtk_psfont_get_gdkfont", _wrap_gtk_psfont_get_gdkfont, 1 },
    { "gtk_psfont_add_font", _wrap_gtk_psfont_add_font, 1 },
    { "gtk_psfont_add_i18n_font", _wrap_gtk_psfont_add_i18n_font, 1 },
    { "gtk_psfont_find_by_family", _wrap_gtk_psfont_find_by_family, 1 },
    { "gtk_psfont_get_families", _wrap_gtk_psfont_get_families, 1 },
#include "gtkextramodule_defs.h"
    { NULL, NULL, 0 }
};

void init_gtkextra(void)
{
    PyObject *m, *d;

    m = Py_InitModule("_gtkextra", _gtkextraMethods);
    d = PyModule_GetDict(m);
    init_pygtk();
    _pygtkextra_register_boxed_types(d);
    if (PyErr_Occurred())
	Py_FatalError("cannot initialize module _gtkextra");
}
