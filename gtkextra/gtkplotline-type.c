/* -*- Mode: C; c-basic-offset: 4 -*- */
/*
 * Python bindings for the GtkExtra widget set
 *
 * Copyright (C) 2000-2001 Andreas Voegele
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

#include "pygtkextra-private.h"

/*
 * GtkPlotLine
 *
 * The GtkPlotLine type has the attributes line_style, line_width and
 * color.  It also behaves somewhat like a list with three items.
 *
 * All the wrapper functions that get a GtkPlotLine should parse the
 * argument with the format string "(ifO)".
 */

static void
PyGtkPlotLine_Dealloc(PyGtkPlotLine_Object *self)
{
    PyMem_DEL(self);
}

static PyObject *
PyGtkPlotLine_Repr(PyGtkPlotLine_Object *self)
{
    char buf[256];

    g_snprintf(buf, sizeof(buf), "(%d, %g, <GdkColor (%hu, %hu, %hu)>)",
	       (int) self->line.line_style, (double) self->line.line_width,
	       self->line.color.red, self->line.color.green,
	       self->line.color.blue);
    return PyString_FromString(buf);
}

static struct memberlist PyGtkPlotLine_members[] =
{
    { "line_style", T_INT, offsetof(GtkPlotLine, line_style) },
    { "line_width", T_FLOAT, offsetof(GtkPlotLine, line_width) },
    { "color", -1, 0 },
    { NULL }
};

static PyObject *
PyGtkPlotLine_GetAttr(PyGtkPlotLine_Object *self, char *attr)
{
    if (strcmp(attr, "color") == 0)
	return PyGdkColor_New(&self->line.color);
    return PyMember_Get((char *) &self->line, PyGtkPlotLine_members, attr);
}

static int
PyGtkPlotLine_SetAttr(PyGtkPlotLine_Object *self, char *attr, PyObject *value)
{
    if (strcmp(attr, "color") == 0) {
	if (!PyGdkColor_Check(value)) {
	    PyErr_SetString(PyExc_TypeError, "value must be a GdkColor");
	    return -1;
	}
	self->line.color = *PyGdkColor_Get(value);
	return 0;
    }
    return PyMember_Set((char *) &self->line, PyGtkPlotLine_members, attr,
			value);
}

static int
PyGtkPlotLine_Length(PyGtkPlotLine_Object *self)
{
    return 3;
}

static PyObject *
PyGtkPlotLine_GetItem(PyGtkPlotLine_Object *self, int i)
{
    switch (i) {
    case 0:
	return PyInt_FromLong(self->line.line_style);
    case 1:
	return PyFloat_FromDouble(self->line.line_width);
    case 2:
	return PyGdkColor_New(&self->line.color);
    }
    PyErr_SetString(PyExc_IndexError, "GtkPlotLine index out of range");
    return NULL;
}

static int
PyGtkPlotLine_SetItem(PyGtkPlotLine_Object *self, int i, PyObject *value)
{
    PyObject *number;
    
    switch (i) {
    case 0:
	if (!PyInt_Check(value)) {
	    PyErr_SetString(PyExc_TypeError, "line_style must be integer");
	    return -1;
	}
	self->line.line_style = PyInt_AS_LONG(value);
	break;
    case 1:
	if (!(PyNumber_Check(value) && (number = PyNumber_Float(value)))) {
	    PyErr_SetString(PyExc_TypeError, "line_width must be number");
	    return -1;
	}
	self->line.line_width = (gfloat) PyFloat_AS_DOUBLE(number);
	Py_DECREF(number);
	break;
    case 2:
	if (!PyGdkColor_Check(value)) {
	    PyErr_SetString(PyExc_TypeError, "value must be a GdkColor");
	    return -1;
	}
	self->line.color = *PyGdkColor_Get(value);
	break;
    default:
	PyErr_SetString(PyExc_IndexError,
			"GtkPlotLine assignment index out of range");
	return -1;
    }
    return 0;
}

static PySequenceMethods PyGtkPlotLine_Sequence = {
    (inquiry) PyGtkPlotLine_Length,
    (binaryfunc) 0,
    (intargfunc) 0,
    (intargfunc) PyGtkPlotLine_GetItem,
    (intintargfunc) 0,
    (intobjargproc) PyGtkPlotLine_SetItem,
    (intintobjargproc) 0
};

PyTypeObject PyGtkPlotLine_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkPlotLine",
    sizeof(PyGtkPlotLine_Object),
    0,
    (destructor) PyGtkPlotLine_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkPlotLine_GetAttr,
    (setattrfunc) PyGtkPlotLine_SetAttr,
    (cmpfunc) 0,
    (reprfunc) PyGtkPlotLine_Repr,
    0,
    &PyGtkPlotLine_Sequence,
    0,
};

PyObject *
pygtkextra_plot_line_new(GtkPlotLineStyle line_style, gfloat line_width,
			 GdkColor *color)
{
    PyGtkPlotLine_Object *self;

    self = (PyGtkPlotLine_Object *)
	PyObject_NEW(PyGtkPlotLine_Object, &PyGtkPlotLine_Type);
    if (!self)
	return NULL;
    self->line.line_style = line_style;
    self->line.line_width = line_width;
    self->line.color = *color;
    return (PyObject *) self;
}

PyObject *
PyGtkPlotLine_New(PyObject *self, PyObject *args)
{
    int line_style;
    float line_width;
    PyObject *py_color;
    
    if (!PyArg_ParseTuple(args, "ifO!", &line_style, &line_width,
			  &PyGdkColor_Type, &py_color))
	return NULL;
    return pygtkextra_plot_line_new(line_style, (gfloat) line_width,
				    PyGdkColor_Get(py_color));
}
