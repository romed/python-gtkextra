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
 * GtkPlotText
 */

static void
PyGtkPlotText_Dealloc(PyGtkPlotText_Object *self)
{
    PyMem_DEL(self);
}

static PyObject *
PyGtkPlotText_set_attributes(PyGtkPlotText_Object *self, PyObject *args,
			     PyObject *kwargs)
{
    static char *kwlist[] = { "fontname", "height", "angle", "foreground",
			      "background", "transparent", "justification",
			      "string", NULL };
    char *fontname, *string;
    int angle, height, transparent, justification;
    PyObject *py_foreground = Py_None, *py_background = Py_None;
    GdkColor *foreground = NULL, *background = NULL;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "ziiOOiiz:GtkPlotText.set_attributes",
				     kwlist, &fontname, &height, &angle,
				     &py_foreground, &py_background,
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
    gtk_plot_text_set_attributes(self->text, fontname, height, angle,
				 foreground, background, transparent,
				 justification, string);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
PyGtkPlotText_set_border(PyGtkPlotText_Object *self, PyObject *args,
			 PyObject *kwargs)
{
    static char *kwlist[] = { "style", "space", "width", "shadow_width", NULL };
    int style, space, width, shadow_width;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
				     "iiii:GtkPlotText.set_border", kwlist,
				     &style, &space, &width, &shadow_width))
	return NULL;
    gtk_plot_text_set_border(self->text, style, space, width, shadow_width);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef PyGtkPlotText_methods[] =
{
    { "set_attributes", (PyCFunction) PyGtkPlotText_set_attributes,
      METH_VARARGS|METH_KEYWORDS },
    { "set_border", (PyCFunction) PyGtkPlotText_set_border,
      METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

static PyObject *
PyGtkPlotText_Str(PyGtkPlotText_Object *self)
{
    char *string;

    string = self->text->text;
    return PyString_FromString((string) ? string : "");
}

static PyObject *
PyGtkPlotText_GetAttr(PyGtkPlotText_Object *self, char *attr)
{
    return Py_FindMethod(PyGtkPlotText_methods, (PyObject *) self, attr);
}

static int
PyGtkPlotText_Compare(PyGtkPlotText_Object *self, PyGtkPlotText_Object *v)
{
    if (self->text == v->text) return 0;
    if (self->text > v->text) return -1;
    return 1;
}

PyTypeObject PyGtkPlotText_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkPlotText",
    sizeof(PyGtkPlotText_Object),
    0,
    (destructor) PyGtkPlotText_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkPlotText_GetAttr,
    (setattrfunc) 0,
    (cmpfunc) PyGtkPlotText_Compare,
    (reprfunc) 0,
    0,
    0,
    0,
    (hashfunc) 0,
    (ternaryfunc) 0,
    (reprfunc) PyGtkPlotText_Str,
};

PyObject *
pygtkextra_plot_text_new(GtkPlotText *text) 
{
    PyGtkPlotText_Object *self;

    if (!text) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkPlotText_Object *)
	PyObject_NEW(PyGtkPlotText_Object, &PyGtkPlotText_Type);
    if (!self)
	return NULL;
    self->text = text;
    return (PyObject *) self;
}

int
PyGtkPlotText_Check(PyObject *obj)
{
    return (obj->ob_type == &PyGtkPlotText_Type);
}

GtkPlotText *
PyGtkPlotText_Get(PyObject *obj)
{
    return ((PyGtkPlotText_Object *) obj)->text;
}
