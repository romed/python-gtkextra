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
 * GtkPSFont
 *
 * This type is returned by gtk_psfont_get_font() and
 * gtk_psfont_find_by_family().
 */

static void
PyGtkPSFont_Dealloc(PyGtkPSFont_Object *self)
{
    PyMem_DEL(self);
}

static struct memberlist PyGtkPSFont_members[] =
{
    { "fontname", T_STRING, offsetof(GtkPSFont, fontname), RO },
    { "psname", T_STRING, offsetof(GtkPSFont, psname), RO },
    { "family", T_STRING, offsetof(GtkPSFont, family), RO },
    { "xfont", -1, 0, RO },
    { "i18n_latinfamily", T_STRING, offsetof(GtkPSFont, i18n_latinfamily), RO },
    { "italic", T_INT, offsetof(GtkPSFont, italic), RO },
    { "bold", T_INT, offsetof(GtkPSFont, bold), RO },
    { "vertical", T_INT, offsetof(GtkPSFont, vertical), RO },
    { NULL }
};

static PyObject *
PyGtkPSFont_GetAttr(PyGtkPSFont_Object *self, char *attr)
{
    if (strcmp(attr, "xfont") == 0) {
	int i, size;
	PyObject *tuple;

	size = 0;
	while (size < 2 && self->psfont->xfont[size])
	    ++size;
	tuple = PyTuple_New(size);
	if (!tuple)
	    return NULL;
	for (i = 0; i < size; ++i) {
	    PyObject *xfontname = PyString_FromString(self->psfont->xfont[i]);
	    if (!xfontname) {
		Py_DECREF(tuple);
		return NULL;
	    }
	    PyTuple_SET_ITEM(tuple, i, xfontname);
	}
	return tuple;
    }
    return PyMember_Get((char *) self->psfont, PyGtkPSFont_members, attr);
}

static int
PyGtkPSFont_SetAttr(PyGtkPSFont_Object *self, char *attr,
			PyObject *value)
{
    return PyMember_Set((char *) self->psfont, PyGtkPSFont_members, attr,
			value);
}

static int
PyGtkPSFont_Compare(PyGtkPSFont_Object *self, PyGtkPSFont_Object *v)
{
    if (self->psfont == v->psfont) return 0;
    if (self->psfont > v->psfont) return -1;
    return 1;
}

PyTypeObject PyGtkPSFont_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkPSFont",
    sizeof(PyGtkPSFont_Object),
    0,
    (destructor) PyGtkPSFont_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkPSFont_GetAttr,
    (setattrfunc) PyGtkPSFont_SetAttr,
    (cmpfunc) PyGtkPSFont_Compare,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_psfont_new(GtkPSFont *psfont) 
{
    PyGtkPSFont_Object *self;

    if (!psfont) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkPSFont_Object *)
	PyObject_NEW(PyGtkPSFont_Object, &PyGtkPSFont_Type);
    if (!self)
	return NULL;
    self->psfont = psfont;
    return (PyObject *) self;
}
