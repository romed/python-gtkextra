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
 * GtkSheetChild
 *
 * This type is returned by gtk_sheet_put() and gtk_sheet_get_child_at().
 */

static void
PyGtkSheetChild_Dealloc(PyGtkSheetChild_Object *self)
{
    PyMem_DEL(self);
}

static struct memberlist PyGtkSheetChild_members[] =
{
    { "x", T_INT, offsetof(GtkSheetChild, x), RO },
    { "y", T_INT, offsetof(GtkSheetChild, y), RO },
    { "attached_to_cell", T_INT, offsetof(GtkSheetChild, attached_to_cell), RO },
    { "row", T_INT, offsetof(GtkSheetChild, row), RO },
    { "column", T_INT, offsetof(GtkSheetChild, col), RO },
    { "x_align", T_FLOAT, offsetof(GtkSheetChild, x_align), RO },
    { "y_align", T_FLOAT, offsetof(GtkSheetChild, y_align), RO },
    { NULL }
};

static PyObject *
PyGtkSheetChild_GetAttr(PyGtkSheetChild_Object *self, char *attr)
{
    if (strcmp(attr, "row") == 0) {
	if (self->child.attached_to_cell)
		return PyInt_FromLong(self->child.row);
	PyErr_SetString(PyExc_AttributeError, "child not attached to a cell");
	return NULL;
    }
    if (strcmp(attr, "column") == 0 || strcmp(attr, "col") == 0) {
	if (self->child.attached_to_cell)
	    return PyInt_FromLong(self->child.col);
	PyErr_SetString(PyExc_AttributeError, "child not attached to a cell");
	return NULL;
    }
    return PyMember_Get((char *) &self->child, PyGtkSheetChild_members, attr);
}

static int
PyGtkSheetChild_SetAttr(PyGtkSheetChild_Object *self, char *attr,
			PyObject *value)
{
    return PyMember_Set((char *) &self->child, PyGtkSheetChild_members, attr,
			value);
}

PyTypeObject PyGtkSheetChild_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkSheetChild",
    sizeof(PyGtkSheetChild_Object),
    0,
    (destructor) PyGtkSheetChild_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkSheetChild_GetAttr,
    (setattrfunc) PyGtkSheetChild_SetAttr,
    (cmpfunc) 0,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_sheet_child_new(GtkSheetChild *child) 
{
    PyGtkSheetChild_Object *self;

    if (!child) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkSheetChild_Object *)
	PyObject_NEW(PyGtkSheetChild_Object, &PyGtkSheetChild_Type);
    if (!self)
	return NULL;
    self->child = *child;
    return (PyObject *) self;
}
