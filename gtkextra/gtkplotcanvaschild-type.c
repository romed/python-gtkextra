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
 * GtkPlotCanvasChild
 *
 * This type is returned by gtk_plot_canvas_get_active_item().
 */

static void
PyGtkPlotCanvasChild_Dealloc(PyGtkPlotCanvasChild_Object *self)
{
    PyMem_DEL(self);
}

static PyObject *
PyGtkPlotCanvasChild_set_selection(PyGtkPlotCanvasChild_Object *self,
				   PyObject *args)
{
    int selection;
    
    if (!PyArg_ParseTuple(args, "i:GtkPlotCanvasChild.set_selection",
			  &selection))
	return NULL;
    gtk_plot_canvas_child_set_selection(self->child, selection);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
PyGtkPlotCanvasChild_set_selection_mode(PyGtkPlotCanvasChild_Object *self,
					PyObject *args)
{
    int mode;
    
    if (!PyArg_ParseTuple(args, "i:GtkPlotCanvasChild.set_selection_mode",
			  &mode))
	return NULL;
    gtk_plot_canvas_child_set_selection_mode(self->child, mode);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef PyGtkPlotCanvasChild_methods[] =
{
    { "set_selection", (PyCFunction) PyGtkPlotCanvasChild_set_selection, METH_VARARGS },
    { "set_selection_mode", (PyCFunction) PyGtkPlotCanvasChild_set_selection_mode, METH_VARARGS },
    { NULL, NULL, 0 }
};

static struct memberlist PyGtkPlotCanvasChild_members[] =
{
    { "allocation", -1, 0, RO },
    { "type", T_INT, offsetof(GtkPlotCanvasChild, type), RO },
    { "flags",T_INT, offsetof(GtkPlotCanvasChild, flags), 0 },
    { "selection",T_INT, offsetof(GtkPlotCanvasChild, selection), 0 },
    { "mode",T_INT, offsetof(GtkPlotCanvasChild, mode), 0 },
    { "state", T_UINT, offsetof(GtkPlotCanvasChild, state), RO },
    { "data", -1, 0, RO },
    { NULL }
};

static PyObject *
PyGtkPlotCanvasChild_GetAttr(PyGtkPlotCanvasChild_Object *self, char *attr)
{
    PyObject *value;

    if (strcmp(attr, "allocation") == 0) {
	return Py_BuildValue("(iiii)",
			     (int) self->child->allocation.x,
			     (int) self->child->allocation.y,
			     (int) self->child->allocation.width,
			     (int) self->child->allocation.height);
    } else if (strcmp(attr, "data") == 0) {
	switch (self->child->type) {
	case GTK_PLOT_CANVAS_NONE:
	    Py_INCREF(Py_None);
	    return Py_None;
	case GTK_PLOT_CANVAS_PLOT:
	case GTK_PLOT_CANVAS_DATA:
	case GTK_PLOT_CANVAS_LEGENDS:
	    return PyGtk_New(GTK_OBJECT(self->child->data));
	case GTK_PLOT_CANVAS_TEXT:
	    return pygtkextra_plot_text_new((GtkPlotText *)
					    self->child->data);
	default:
	    return PyCObject_FromVoidPtr(self->child->data, NULL);
	}
    }
    value = PyMember_Get((char *) self->child, PyGtkPlotCanvasChild_members,
			 attr);
    if (!value) {
	if (PyErr_ExceptionMatches(PyExc_AttributeError)) {
	    PyErr_Clear();
	    value = Py_FindMethod(PyGtkPlotCanvasChild_methods,
				  (PyObject *) self, attr);
	}
    }
    return value;
}

static int
PyGtkPlotCanvasChild_SetAttr(PyGtkPlotCanvasChild_Object *self, char *attr,
			     PyObject *value)
{
    return PyMember_Set((char *) self->child, PyGtkPlotCanvasChild_members,
			attr, value);
}

static int
PyGtkPlotCanvasChild_Compare(PyGtkPlotCanvasChild_Object *self,
			     PyGtkPlotCanvasChild_Object *v)
{
    if (self->child == v->child) return 0;
    if (self->child > v->child) return -1;
    return 1;
}

PyTypeObject PyGtkPlotCanvasChild_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkPlotCanvasChild",
    sizeof(PyGtkPlotCanvasChild_Object),
    0,
    (destructor) PyGtkPlotCanvasChild_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkPlotCanvasChild_GetAttr,
    (setattrfunc) PyGtkPlotCanvasChild_SetAttr,
    (cmpfunc) PyGtkPlotCanvasChild_Compare,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_plot_canvas_child_new(GtkPlotCanvasChild *child)
{
    PyGtkPlotCanvasChild_Object *self;

    if (!child) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkPlotCanvasChild_Object *)
	PyObject_NEW(PyGtkPlotCanvasChild_Object, &PyGtkPlotCanvasChild_Type);
    if (!self)
	return NULL;
    self->child = child;
    return (PyObject *) self;
}

int
PyGtkPlotCanvasChild_Check(PyObject *obj)
{
    return (obj->ob_type == &PyGtkPlotCanvasChild_Type);
}

GtkPlotCanvasChild *
PyGtkPlotCanvasChild_Get(PyObject *obj)
{
    return ((PyGtkPlotCanvasChild_Object *) obj)->child;
}
